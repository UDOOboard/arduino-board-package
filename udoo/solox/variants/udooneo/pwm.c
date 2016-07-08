/*
 * Copyright (c) 2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "mqx.h"
#include "bsp.h"
#include "log_mqx.h"

#include "pwm_ifc.h"

/*  From IMX6SXRM.pdf 49.7.5
 *  PWM (Hz) = PCLK (Hz) / (period + 2)
 *
 *  PCLK = SRC_CLK / prescaler+1
 *  SRC_CLK = 24000000 (Hz) when kPwmClockSourceIpg is configured (pwm_set_clock(pwmChn, kPwmClockSourceIpg))
 *
*/

#define NMAX_PWMS   8
static PWM_SETUP_STRUCT pwmSetup[NMAX_PWMS] = {0};

void pwm_enable(uint16_t instance)
{
    MY_HW_PWM_PWMCR(instance).B.EN = 1;
    pwmSetup[instance].enabled = 1;
}

bool PwmIsEnabled(uint16_t instance)
{
    return (pwmSetup[instance].enabled == 1);
}

void pwm_disable(uint16_t instance)
{
    // Disable PWM interrupt
    MY_HW_PWM_PWMCR(instance).B.EN = 0;
    pwmSetup[instance].enabled = 0;
}

/*
//! @brief Clock sources for the PWM.
kPwmClockSourceNone = 0,
kPwmClockSourceIpg = 1,
kPwmClockSourceCkih = 2,
kPwmClockSourceCkil = 3
*/
void pwm_set_clock(uint16_t instance, uint16_t clkSrc)
{
    MY_HW_PWM_PWMCR(instance).B.CLKSRC = clkSrc;
}

// Set FIFO watermark 0 to 3
void pwm_set_fwm(uint16_t instance, uint16_t fwm)
{
    MY_HW_PWM_PWMCR(instance).B.FWM = fwm;
}

// Set prescale after checking its range.
// 0 - divide by 1, 1 - divide by 2, 4095 divide by 4096
void pwm_set_prescaler(uint16_t instance, uint16_t prescale)
{
    if (prescale > PWM_MAX_PRESCALER) {
        printf("Invalid prescaler value.\n");
        return;
    }

    MY_HW_PWM_PWMCR(instance).B.PRESCALER = prescale;
}

// Set active polarity: 0 set at rollover, 1 clear at rollover
void pwm_set_poutc(uint16_t instance, uint16_t poutc)
{
    MY_HW_PWM_PWMCR(instance).B.POUTC = poutc;
}

// Set period from 0 to 0xFFFE
// when this function is called, must be called pwm_set_tesolution
void pwm_set_period(uint16_t instance, uint16_t period)
{
    MY_HW_PWM_PWMPR(instance).B.PERIOD = period;
    pwmSetup[instance].period = period;
}

uint16_t pwm_get_period(uint16_t instance)
{
    return (pwmSetup[instance].period);
}

// Set sample repeat from 0 to 3
void pwm_set_repeat(uint16_t instance, uint16_t repeat)
{
    MY_HW_PWM_PWMCR(instance).B.REPEAT = repeat;
}

// Set sample
// depend on period setting
// sample = 0 to period+1
bool pwm_set_sample(uint16_t instance, uint16_t sample)
{
    if (MY_HW_PWM_PWMSR(instance).B.FE) {
        MY_HW_PWM_PWMSAR(instance).B.SAMPLE = sample;
        return (TRUE);
    }
    else {
        printf("PWM FIFO sample is full!!!.\n");
        return (FALSE);
    }
}

void pwm_set_resolution(uint16_t instance, uint32_t value)
{
    pwmSetup[instance].resolution = value;
}

uint32_t pwm_get_resolution(uint16_t instance)
{
    return (pwmSetup[instance].resolution);
}

#ifdef INTERRUPT_VERSION_PWM

//! IRQ id of pwm
#define PWM_IRQS(x) \
    ((x) == HW_PWM1 ? INT_PWM1_PWM5 : \
     (x) == HW_PWM2 ? INT_PWM2_PWM6 : \
     (x) == HW_PWM3 ? INT_PWM3_PWM7 : \
     (x) == HW_PWM4 ? INT_PWM4_PWM8 : \
     (x) == HW_PWM5 ? INT_PWM1_PWM5 : \
     (x) == HW_PWM6 ? INT_PWM2_PWM6 : \
     (x) == HW_PWM7 ? INT_PWM3_PWM7 : \
     (x) == HW_PWM8 ? INT_PWM4_PWM8 : 0xFFFFFFFF)
#define NMAX_PWM_SAMPLE 24

struct pwm_interrupt_status pwm_int_test_end;
uint16_t pwmSample[NMAX_PWM_SAMPLE] = {2500, 5000, 7500, 10000, 12500, 15000,
    17500, 20000, 22500, 25000, 27500, 30000, 32500, 35000, 37500, 40000,
    42500, 45000, 47500, 50000, 52500, 55000, 57500, 60000};
uint16_t pwmSampleCnt=0;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////
int pwm_init(uint32_t instance)
{
    int idx;

    // Disable PWM first
    MY_HW_PWM_PWMCR(instance).B.EN = 0;

    MY_HW_PWM_PWMCR(instance).B.CLKSRC = kPwmClockSourceIpg;

    // Set FIFO watermark to 4 empty slots
    MY_HW_PWM_PWMCR(instance).B.FWM = 3;

    // 0 - divide by 1, 1 - divide by 2
    MY_HW_PWM_PWMCR(instance).B.PRESCALER = 0;

    // Set active polarity: 0 set at rollover, 1 clear at rollover
    MY_HW_PWM_PWMCR(instance).B.POUTC = 0;

    // Set period
    MY_HW_PWM_PWMPR(instance).B.PERIOD = 0xfffe;

    // Set sample repeat
    MY_HW_PWM_PWMCR(instance).B.REPEAT = 0;

    for (idx = 0; idx < 3; idx++) {
        MY_HW_PWM_PWMSAR(instance).B.SAMPLE = pwmSample[idx];
    }

    // Setup interrupt for FIFO empty
    /* register FIFO Empty interrupt to end the output test */
    pwm_int_test_end.instance = instance;
    pwm_int_test_end.interrupt = kPwmFifoEmptyIrq;
    return TRUE;
}

void pwm_clear_int_status(uint32_t instance, uint32_t mask)
{
    // Convert mask from abstract constants to register bitmasks.
    uint32_t convertedMask = 0;
    if (mask & kPwmFifoEmptyIrq) {
        convertedMask |= BM_PWM_PWMSR_FE;
    }
    if (mask & kPwmRolloverIrq) {
        convertedMask |= BM_PWM_PWMSR_ROV;
    }
    if (mask & kPwmCompareIrq) {
        convertedMask |= BM_PWM_PWMSR_CMP;
    }
    // Clear status bits by writing 1s.
    MY_HW_PWM_PWMSR(instance).U =  convertedMask;
}

void pwm_enable_interrupt(uint32_t irq_id)
{
    _bsp_int_init(irq_id, 3, 0, true);
}

void pwm_disable_interrupt(uint32_t irq_id)
{
    _bsp_int_init(irq_id, 3, 0, false);
}

void pwm_setup_interrupt(uint32_t instance, void (*irq_subroutine) (void *), uint8_t mask)
{
    int irq_id = PWM_IRQS(instance);

    // Disable the IRQ first
    //disable_interrupt(irq_id, CPU_0);
    pwm_disable_interrupt(irq_id);

    // Clear status register
    MY_HW_PWM_PWMSR(instance).U = (BM_PWM_PWMSR_FE | BM_PWM_PWMSR_ROV |
				   BM_PWM_PWMSR_CMP | BM_PWM_PWMSR_FWE);
    // Register the IRQ sub-routine
    //register_interrupt_routine(irq_id, irq_subroutine);
    _int_install_isr(irq_id, irq_subroutine, 0);

    // Enable the IRQ at ARM core level
    //enable_interrupt(irq_id, CPU_0, 0);
    pwm_enable_interrupt(irq_id);

    // Enable interrupt to status
    MY_HW_PWM_PWMIR(instance).B.FIE = ((mask & kPwmFifoEmptyIrq) != 0);
    MY_HW_PWM_PWMIR(instance).B.RIE = ((mask & kPwmRolloverIrq) != 0);
    MY_HW_PWM_PWMIR(instance).B.CIE = ((mask & kPwmCompareIrq) != 0);
}

void pwm_free_interrupt(uint32_t instance)
{
    int irq_id = PWM_IRQS(instance);

    // Disable the IRQ at ARM core level
    //disable_interrupt(irq_id, CPU_0);
    pwm_disable_interrupt(irq_id);

    // Clear all interrupt enables.
    MY_HW_PWM_PWMIR(instance).U =  0;
}

void pwm_isr_test_end(void)
{
    // Clear Interrupt status
    pwm_clear_int_status(pwm_int_test_end.instance, pwm_int_test_end.interrupt);

    // Set PWM output end flag
    //g_pwm_test_end = TRUE;
}

void TestIntPwm(void)
{
    _bsp_pwm_io_init(0, 0xff);
    pwm_init(0);
    // Disable PWM first
    MY_HW_PWM_PWMCR(0).B.EN = 1;

    while (1) { _time_delay(10); };

    _bsp_pwm_io_init(0, 0x00);
}

#endif

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
