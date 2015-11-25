#ifndef FSL_FlexCAN_INT_h
#define FSL_FlexCAN_INT_h 1
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
*   This include file is used to provide constant and structure definitions
*   specific to the FlexCAN Serial Communications Controller
*   Revision History:
*   Apr 21, 2003   2.50          Initial version
*
*
*END************************************************************************/

#include <mqx.h>
#include <psp.h>

#include "clk_name.h"

// concrete HW settings:

#define FLEXCAN_MESSBUF_INT_LEVEL       (3)
#define FLEXCAN_MESSBUF_INT_SUBLEVEL    (4)

#define FLEXCAN_ERROR_INT_LEVEL         (3)
#define FLEXCAN_ERROR_INT_SUBLEVEL      (2)

#define FLEXCAN_BUSOFF_INT_LEVEL        (3)
#define FLEXCAN_BUSOFF_INT_SUBLEVEL     (3)

#define FLEXCAN_WAKEUP_INT_LEVEL        (3)
#define FLEXCAN_WAKEUP_INT_SUBLEVEL     (1)

#define FLEXCAN_MSG_BUFADDR_OFFSET      (128)
#define FLEXCAN_MSG_BUFF_MAXDATA_SIZE   (8)

#ifndef FLEXCAN_IPBUS_CLK
#define FLEXCAN_IPBUS_CLK               (BSP_BUS_CLOCK) /* Indicates internal clock source */
#endif
#ifndef FLEXCAN_OSC_CLK
#define FLEXCAN_OSC_CLK                 (0) /* Must be set to external clock frequency, different to FLEXCAN_IPBUS_CLK! */
#endif

/*
** CAN interrupt types enum
*/
#define FLEXCAN_INT_BUF                 (0)
#if !defined(BSP_VYBRID_AUTOEVB_A5) || !defined(BSP_TWR_VF65GS10_A5)
#define FLEXCAN_INT_ERR                 (1)
#define FLEXCAN_INT_BOFF                (2)
#define FLEXCAN_INT_WAKEUP              (3)
#endif

/*
** CAN wakeup interrupt mask
*/
#if defined(BSP_VYBRID_AUTOEVB_A5) || defined(BSP_TWR_VF65GS10_A5)
#define CAN_MCR_WAKMSK_MASK             (0x0)
#define CAN_ESR1_WAKINT_MASK            (0x0)
#endif

#ifdef __cplusplus
extern "C" {
#endif
uint32_t flexcan_int_enable(uint8_t,uint32_t);
uint32_t flexcan_int_disable(uint8_t,uint32_t);
uint32_t flexcan_install_isr(uint8_t,uint32_t,INT_ISR_FPTR);

#if !(defined(BSP_IMX6SX_PELE_M4) || defined(BSP_IMX6SX_SDB_M4) ||\
      defined(BSP_VYBRID_AUTOEVB_A5) || defined(BSP_VYBRID_AUTOEVB_M4) ||\
      defined(BSP_TWR_VF65GS10_A5) || defined(BSP_TWR_VF65GS10_M4) ||\
      defined(BSP_IMX6SX_AI_M4))
uint32_t flexcan_error_int_enable(uint8_t);
uint32_t flexcan_error_int_disable(uint8_t);
uint32_t flexcan_install_isr_err_int(uint8_t,INT_ISR_FPTR);
uint32_t flexcan_install_isr_boff_int(uint8_t,INT_ISR_FPTR);
uint32_t flexcan_install_isr_wake_int(uint8_t,INT_ISR_FPTR);
#endif

#ifdef __cplusplus
}
#endif

#endif
/* EOF */
