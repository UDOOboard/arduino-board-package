/*HEADER**********************************************************************
*
* Copyright 2011 Freescale Semiconductor, Inc.
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
*   Clock manager imx6sx specific definitions.
*
*
*END************************************************************************/

#ifndef __cm_imx6sx_h__
#define __cm_imx6sx_h__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum  {
    CM_CLOCK_PLL1 = 1,  /*ARM*/
    CM_CLOCK_PLL2,      /*BUS*/
    CM_CLOCK_PLL3,      /*USBOTG*/
    CM_CLOCK_PLL4,      /*AUDIO*/
    CM_CLOCK_PLL5,      /*VIDEO*/
    CM_CLOCK_PLL6,      /*NET*/
    CM_CLOCK_PLL7,      /*USBHOST*/
} CM_CLOCK_PLL;

typedef enum  {
    CM_CLOCK_PLL_main = 0,
    CM_CLOCK_PLL_PFD0 = 1,
    CM_CLOCK_PLL_PFD1,
    CM_CLOCK_PLL_PFD2,
    CM_CLOCK_PLL_PFD3,
} CM_CLOCK_PLL_PFD;

typedef enum  {
    CM_CLOCK_SOURCE_CORE = 0,   /*M4*/
    CM_CLOCK_SOURCE_CKIL,
    CM_CLOCK_SOURCE_OSC,
    CM_CLOCK_SOURCE_BUS,        /*PLL2*/
    CM_CLOCK_SOURCE_IPG,        /*IPG*/
    CM_CLOCK_SOURCE_PLL2_PFD0,
    CM_CLOCK_SOURCE_PLL2_PFD2,
    CM_CLOCK_SOURCE_PLL3,       /*480M USB*/
    CM_CLOCK_SOURCE_PLL3_PFD2,  /*508M*/
    CM_CLOCK_SOURCE_PLL3_PFD3,  /*454M*/
    CM_CLOCK_SOURCE_PLL4,       /*650M*/
    CM_CLOCK_SOURCES,            /* Number of clock sources available */
    CM_CLOCK_SOURCE_SYSTEM = CM_CLOCK_SOURCE_CORE
} CM_CLOCK_SOURCE;

#ifdef __cplusplus
}
#endif


#endif /* __cm_imx6sx_h__ */
