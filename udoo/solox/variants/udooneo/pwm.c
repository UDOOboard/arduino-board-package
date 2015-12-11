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

#define NMAX_PWMS	8
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
    //fefrpwm_free_interrupt(instance);
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

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
