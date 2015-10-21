/*HEADER**********************************************************************
*
* Copyright 2008-2014 Freescale Semiconductor, Inc.
* Copyright 2004-2008 Embedded Access Inc.
* Copyright 1989-2008 ARC International
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file contains the definitions of constants and structures
*   required for the sci drivers.
*
*
*END************************************************************************/
#ifndef _serial_imx_uart_h_
#define _serial_imx_uart_h_

#if MQX_ENABLE_LOW_POWER

/*
** IMX_UART_CLOCK_CONFIGURATION_STRUCT
**
** This structure defines the behavior of IMX_UART in specific
** low power clock configuration.
*/
typedef struct imx_uart_clock_configuration_struct
{
    /* Whether channel is enabled in particular clock configuration */
    uint8_t      ENABLED;

} IMX_UART_CLOCK_CONFIGURATION_STRUCT, * IMX_UART_CLOCK_CONFIGURATION_STRUCT_PTR;
typedef const IMX_UART_CLOCK_CONFIGURATION_STRUCT * IMX_UART_CLOCK_CONFIGURATION_STRUCT_CPTR;

/*
** IMX_UART_OPERATION_MODE_STRUCT
**
** This structure defines the behavior of IMX_UART in specific
** low power operation mode.
*/
typedef struct imx_uart_operation_mode_struct
{
    /* HW/wakeup enable/disable flags */
    uint8_t      FLAGS;

    /* Wakeup register bits combination: UART_C2_RWU_MASK, UART_C1_WAKE_MASK, UART_C1_ILT_MASK, UART_C4_MAEN1_MASK, UART_C4_MAEN2_MASK */
    uint8_t      WAKEUP_BITS;

    /* Wakeup settings of register UART_MA1 */
    uint8_t      MA1;

    /* Wakeup settings of register UART_MA2 */
    uint8_t      MA2;

} IMX_UART_OPERATION_MODE_STRUCT, * IMX_UART_OPERATION_MODE_STRUCT_PTR;
typedef const IMX_UART_OPERATION_MODE_STRUCT * IMX_UART_OPERATION_MODE_STRUCT_CPTR;

/*
**
** IO SERIAL LPM STRUCT
**
** This structure is used to store information regarding low power functionality.
**
*/
typedef struct io_serial_lpm_struct
{
   /* Low power manager registration handle */
   _mqx_uint           REGISTRATION_HANDLE;

   /* Low level device lock */
   LWSEM_STRUCT        LOCK;

   /* Special flags */
   uint8_t              FLAGS;

} IO_SERIAL_LPM_STRUCT, * IO_SERIAL_LPM_STRUCT_PTR;

#endif

/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/
/*
** IMX_UART_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a serial port is initialized.
*/
typedef struct imx_uart_init_struct
{

   /* The size of the queues to buffer incoming/outgoing data */
   uint32_t QUEUE_SIZE;

   /* The device to initialize */
   uint32_t DEVICE;

   /* The clock speed of cpu */
   uint32_t CLOCK_SPEED;

   /* The baud rate for the channel */
   uint32_t BAUD_RATE;

   /* RX / TX interrupt vector */
   uint32_t RX_TX_VECTOR;

   /* ERR interrupt vector */
   uint32_t ERR_VECTOR;

   /* RX / TX interrupt vector priority */
   uint32_t RX_TX_PRIORITY;

   /* ERR interrupt vector priority */
   uint32_t ERR_PRIORITY;
} IMX_UART_INIT_STRUCT, * IMX_UART_INIT_STRUCT_PTR;
typedef const IMX_UART_INIT_STRUCT * IMX_UART_INIT_STRUCT_CPTR;

/*
** IMX_UART_INFO_STRUCT
** Run time state information for each serial channel
*/
typedef struct imx_uart_info_struct
{
   /* The current init values for this port */
   IMX_UART_INIT_STRUCT          INIT;

   /* The sci device register */
   UART_MemMapPtr             SCI_PTR;

   /* clock entry for module and ipg*/
   void*      SERIAL_CLK;
   void*      SERIAL_IPG_CLK;

   /* The previous interrupt handler and data */
   void       (_CODE_PTR_ OLD_ISR)(void *);
   void       (_CODE_PTR_ OLD_ISR_EXCEPTION_HANDLER)(uint32_t, uint32_t, void *,
               void *);
   void                             *OLD_ISR_DATA;

   /* Various flags */
   uint32_t                           FLAGS;

   /* Statistical information */
   uint32_t                           INTERRUPTS;
   uint32_t                           RX_CHARS;
   uint32_t                           TX_CHARS;
   uint32_t                           RX_BREAKS;
   uint32_t                           RX_PARITY_ERRORS;
   uint32_t                           RX_FRAMING_ERRORS;
   uint32_t                           RX_OVERRUNS;
   uint32_t                           RX_DROPPED_INPUT;
   uint32_t                           RX_NOISE_ERRORS;
} IMX_UART_INFO_STRUCT, * IMX_UART_INFO_STRUCT_PTR;

/*--------------------------------------------------------------------------*/
/*
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif

uint32_t _imx_uart_polled_install(char *, IMX_UART_INIT_STRUCT_CPTR, uint32_t);
uint32_t _imx_uart_int_install(char *, IMX_UART_INIT_STRUCT_CPTR, uint32_t);
void    *_bsp_get_serial_base_address(uint8_t);

#ifdef __cplusplus
}
#endif

#endif //_serial_imx_uart_h_

/* EOF */
