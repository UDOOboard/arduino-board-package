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
*   WKPU imx6sx specific function prototypes.
*
*
*END************************************************************************/

#ifndef __imx6sx_wkpu_h__
#define __imx6sx_wkpu_h__

void wkpu_wakeup_enable(uint32_t source);
void wkpu_clear_wakeup(uint32_t source);
uint32_t wkpu_int_get_vector(void);

#endif
