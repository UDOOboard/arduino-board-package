/*HEADER**********************************************************************
*
* Copyright 2013-2014 Freescale Semiconductor, Inc.
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
*   clock tree management APIs header file
*
*
*END************************************************************************/

#ifndef __clk_api_h__
#define __clk_api_h__

#include "mqx.h"
#include "stdarg.h"
#include "clk_name.h"

#define BSP_CLKAPI_SETFREQ_OK                   0x0
#define BSP_CLKAPI_SETFREQ_NO_CHANGE            0xFF

#define LINUX_STATUS_READY                      1
#define LINUX_STATUS_NOT_READY                  0

#ifdef __cplusplus
extern "C" {
#endif
/*
 * get clock node
 */
void* clock_get(CLOCK_NAME clk_name);

/*
 * get clock string
 */
char* clock_get_name(void* pclk);

/*
 * enable clock
 */
void clock_enable(void* pclk);


/*
 * disable clock
 */
void clock_disable(void* pclk);

/*
 * query peer status
 */
uint32_t clock_query_peer_status(void);

/*
 * get clock parent
 */
void* clock_get_parent(void* pclk);

/*
 * set clock parent
 */
void* clock_set_parent(void* pclk, void* pclkparent);

/*
 * get clock freq
 */
uint32_t clock_get_freq(void* pclk);

/*
 * set clock freq
 */
uint8_t clock_set_freq(void* pclk, ...);

/*
 * dump clock
 */
void clock_dump(void* p_clk);
void clock_dump_all(void);

void clock_dump_simple(void* p_clk);
void clock_dump_all_simple(void);
int clock_get_nodes_cnt(void);

#ifdef __cplusplus
}
#endif

#endif
