/*HEADER**********************************************************************
*
* Copyright 2013 Freescale Semiconductor, Inc.
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
*   Clock name enumeration definition for Vybrid
*
*
*END************************************************************************/

#ifndef __clk_name_h__
#define __clk_name_h__

typedef enum _clockNames {
    CLK_CKIL,
    CLK_OSC,
    CLK_PLL2,
    CLK_PLL2_PFD0,
    CLK_PLL2_PFD2,
    CLK_PLL2_PFD0_DIV,
    CLK_PLL3,
    CLK_PLL3_PFD1,
    CLK_PLL3_PFD2,
    CLK_PLL3_PFD3,
    CLK_PLL3_80,
    CLK_PLL3_60,
    CLK_PLL4,
    CLK_PLL5,
    CLK_PRE_PERIPH,
    CLK_PERIPH2,
    CLK_PERIPH,
    CLK_AHB,
    CLK_IPG,
    CLK_PERCLK,
    CLK_M4,
    CLK_ALT_OCRAM,
    CLK_OCRAM,
    CLK_FLEXCAN1,
    CLK_FLEXCAN1_IPG,
    CLK_FLEXCAN2,
    CLK_FLEXCAN2_IPG,
    CLK_CANFD,
    CLK_ECSPI1,
    CLK_ECSPI2,
    CLK_ECSPI3,
    CLK_ECSPI4,
    CLK_ECSPI5,
    CLK_QSPI1,
    CLK_QSPI2,
    CLK_SSI1,
    CLK_SSI2,
    CLK_SSI3,
    CLK_UART,
    CLK_UART_IPG,
    CLK_I2C1,
    CLK_I2C2,
    CLK_I2C3,
    CLK_I2C4,
    CLK_EPIT1,
    CLK_EPIT2,
    CLK_MAX
} CLOCK_NAME;


#endif
