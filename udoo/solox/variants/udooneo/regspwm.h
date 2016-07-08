#ifndef __HW_PWM_REGISTERS_H__
#define __HW_PWM_REGISTERS_H__

/*
 * i.MX6DQ PWM
 *
 * PWM
 *
 * Registers defined in this header file:
 * - HW_PWM_PWMCR - PWM Control Register
 * - HW_PWM_PWMSR - PWM Status Register
 * - HW_PWM_PWMIR - PWM Interrupt Register
 * - HW_PWM_PWMSAR - PWM Sample Register
 * - HW_PWM_PWMPR - PWM Period Register
 * - HW_PWM_PWMCNR - PWM Counter Register
 *
 * - hw_pwm_t - Struct containing all module registers.
 */

//! @name Module base addresses
//@{
#define REGS_PWM1_BASE (0x42080000u) //!< Base address for PWM instance number 1.
#define REGS_PWM2_BASE (0x42084000u) //!< Base address for PWM instance number 2.
#define REGS_PWM3_BASE (0x42088000u) //!< Base address for PWM instance number 3.
#define REGS_PWM4_BASE (0x4208C000u) //!< Base address for PWM instance number 4.
#define REGS_PWM5_BASE (0x422A4000u) //!< Base address for PWM instance number 4.
#define REGS_PWM6_BASE (0x422A8000u) //!< Base address for PWM instance number 4.
#define REGS_PWM7_BASE (0x422AC000u) //!< Base address for PWM instance number 4.
#define REGS_PWM8_BASE (0x422B0000u) //!< Base address for PWM instance number 4.

#define BP_PWM_PWMCR_PRESCALER      (4)      //!< Bit position for PWM_PWMCR_PRESCALER.
#define BM_PWM_PWMCR_PRESCALER      (0x0000fff0)  //!< Bit mask for PWM_PWMCR_PRESCALER.
#define PWM_MAX_PRESCALER      		(0x00000fff)

#ifdef INTERRUPT_VERSION_PWM

#define BM_PWM_PWMSR_FE				(0x00000008)
#define BM_PWM_PWMSR_ROV			(0x00000010)
#define BM_PWM_PWMSR_CMP			(0x00000020)
#define BM_PWM_PWMSR_FWE			(0x00000040)

#define HW_PWM1						(0)
#define HW_PWM2						(1)
#define HW_PWM3						(2)
#define HW_PWM4						(3)
#define HW_PWM5						(4)
#define HW_PWM6						(5)
#define HW_PWM7						(6)
#define HW_PWM8						(7)

#endif
//-------------------------------------------------------------------------------------------
// HW_PWM_PWMCR - PWM Control Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMCR - PWM Control Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The PWM control register (PWM_PWMCR) is used to configure the operating settings of the PWM. It
 * contains the prescaler for the clock division.
 */
typedef union _hw_pwm_pwmcr
{
    uint32_t U;
    struct _hw_pwm_pwmcr_bitfields
    {
        unsigned EN : 1; //!< [0] PWM Enable.
        unsigned REPEAT : 2; //!< [2:1] Sample Repeat.
        unsigned SWR : 1; //!< [3] Software Reset.
        unsigned PRESCALER : 12; //!< [15:4] Counter Clock Prescaler Value.
        unsigned CLKSRC : 2; //!< [17:16] Select Clock Source.
        unsigned POUTC : 2; //!< [19:18] PWM Output Configuration.
        unsigned HCTR : 1; //!< [20] Half-word Data Swap Control.
        unsigned BCTR : 1; //!< [21] Byte Data Swap Control.
        unsigned DBGEN : 1; //!< [22] Debug Mode Enable.
        unsigned WAITEN : 1; //!< [23] Wait Mode Enable.
        unsigned DOZEN : 1; //!< [24] Doze Mode Enable.
        unsigned STOPEN : 1; //!< [25] Stop Mode Enable.
        unsigned FWM : 2; //!< [27:26] FIFO Water Mark.
        unsigned RESERVED0 : 4; //!< [31:28] Reserved.
    } B;
} hw_pwm_pwmcr_t;

//-------------------------------------------------------------------------------------------
// HW_PWM_PWMSR - PWM Status Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMSR - PWM Status Register (W1C)
 *
 * Reset value: 0x00000008
 *
 * The PWM status register (PWM_PWMSR) contains seven bits which display the state of the FIFO and
 * the occurrence of rollover and compare events. The FIFOAV bit is read-only but the other four
 * bits can be cleared by writing 1 to them. The FE, ROV, and CMP bits are associated with FIFO-
 * Empty, Roll-over, and Compare interrupts, respectively.
 */
typedef union _hw_pwm_pwmsr
{
    uint32_t U;
    struct _hw_pwm_pwmsr_bitfields
    {
        unsigned FIFOAV : 3; //!< [2:0] FIFO Available.
        unsigned FE : 1; //!< [3] FIFO Empty Status Bit.
        unsigned ROV : 1; //!< [4] Roll-over Status.
        unsigned CMP : 1; //!< [5] Compare Status.
        unsigned FWE : 1; //!< [6] FIFO Write Error Status.
        unsigned RESERVED0 : 25; //!< [31:7] Reserved.
    } B;
} hw_pwm_pwmsr_t;

//-------------------------------------------------------------------------------------------
// HW_PWM_PWMIR - PWM Interrupt Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMIR - PWM Interrupt Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The PWM Interrupt register (PWM_PWMIR) contains three bits which control the generation of the
 * compare, rollover and FIFO empty interrupts.
 */
typedef union _hw_pwm_pwmir
{
    uint32_t U;
    struct _hw_pwm_pwmir_bitfields
    {
        unsigned FIE : 1; //!< [0] FIFO Empty Interrupt Enable.
        unsigned RIE : 1; //!< [1] Roll-over Interrupt Enable.
        unsigned CIE : 1; //!< [2] Compare Interrupt Enable.
        unsigned RESERVED0 : 29; //!< [31:3] Reserved.
    } B;
} hw_pwm_pwmir_t;

//-------------------------------------------------------------------------------------------
// HW_PWM_PWMSAR - PWM Sample Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMSAR - PWM Sample Register (RW)
 *
 * Reset value: 0x00000000
 *
 * The PWM sample register (PWM_PWMSAR) is the input to the FIFO. 16-bit words are loaded into the
 * FIFO. The FIFO can be written at any time, but can be read only when the PWM is enabled. The PWM
 * will run at the last set duty-cycle setting if all the values of the FIFO has been utilized,
 * until the FIFO is reloaded or the PWM is disabled. When a new value is written, the duty cycle
 * changes after the current period is over. A value of zero in the sample register will result in
 * the PWMO output signal always being low/high (POUTC = 00 it will be low and POUTC = 01 it will be
 * high), and no output waveform will be produced. If the value in this register is higher than the
 * PERIOD + 1, the output will never be set/reset depending on POUTC value.
 */
typedef union _hw_pwm_pwmsar
{
    uint32_t U;
    struct _hw_pwm_pwmsar_bitfields
    {
        unsigned SAMPLE : 16; //!< [15:0] Sample Value.
        unsigned RESERVED0 : 16; //!< [31:16] These are reserved bits and writing a value will not affect the functionality of PWM and are always read as zero.
    } B;
} hw_pwm_pwmsar_t;

//-------------------------------------------------------------------------------------------
// HW_PWM_PWMPR - PWM Period Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMPR - PWM Period Register (RW)
 *
 * Reset value: 0x0000fffe
 *
 * The PWM period register (PWM_PWMPR) determines the period of the PWM output signal. After the
 * counter value matches PERIOD + 1, the counter is reset to start another period. PWMO (Hz) =
 * PCLK(Hz) / (period +2) A value of zero in the PWM_PWMPR will result in a period of two clock
 * cycles for the output signal. Writing 0xFFFF to this register will achieve the same result as
 * writing 0xFFFE. A change in the period value due to a write in PWM_PWMPR results in the counter
 * being reset to zero and the start of a new count period. Settings PWM_PWMPR to 0xFFFF when
 * PWMx_PWMCR REPEAT bits are set to non-zero values is not allowed.
 */
typedef union _hw_pwm_pwmpr
{
    uint32_t U;
    struct _hw_pwm_pwmpr_bitfields
    {
        unsigned PERIOD : 16; //!< [15:0] Period Value.
        unsigned RESERVED0 : 16; //!< [31:16] These are reserved bits and writing a value will not affect the functionality of PWM and are always read as zero.
    } B;
} hw_pwm_pwmpr_t;
//-------------------------------------------------------------------------------------------
// HW_PWM_PWMCNR - PWM Counter Register
//-------------------------------------------------------------------------------------------

/*!
 * @brief HW_PWM_PWMCNR - PWM Counter Register (RO)
 *
 * Reset value: 0x00000000
 *
 * The read-only pulse-width modulator counter register (PWM_PWMCNR) contains the current count
 * value and can be read at any time without disturbing the counter.
 */
typedef union _hw_pwm_pwmcnr
{
    uint32_t U;
    struct _hw_pwm_pwmcnr_bitfields
    {
        unsigned COUNT : 16; //!< [15:0] Counter Value.
        unsigned RESERVED0 : 16; //!< [31:16] These are reserved bits and writing a value will not affect the functionality of PWM and are always read as zero.
    } B;
} hw_pwm_pwmcnr_t;

#endif

