/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
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
*   User configuration for MQX components
*
*
*END************************************************************************/

#ifndef __user_config_h__
#define __user_config_h__

/* mandatory CPU identification */
#define MQX_CPU                  PSP_CPU_IMX6SX_M4

/* MGCT: <generated_code> */
#define BSPCFG_ENABLE_TTYA       0
#define BSPCFG_ENABLE_ITTYA      0
#define BSPCFG_ENABLE_TTYB       0
// mqx console port
#define BSPCFG_ENABLE_ITTYB      1
#define BSPCFG_ENABLE_TTYC       0
#define BSPCFG_ENABLE_ITTYC      0
#define BSPCFG_ENABLE_TTYD       0
#define BSPCFG_ENABLE_ITTYD      0
#define BSPCFG_ENABLE_TTYE       0
#define BSPCFG_ENABLE_ITTYE      0
#define BSPCFG_ENABLE_TTYF       0
#define BSPCFG_ENABLE_ITTYF      0
#define BSPCFG_ENABLE_I2C1       0
#define BSPCFG_ENABLE_II2C1      0
#define BSPCFG_ENABLE_I2C2       0
#define BSPCFG_ENABLE_II2C2      0
#define BSPCFG_ENABLE_I2C3       0
#define BSPCFG_ENABLE_II2C3      0
#define BSPCFG_ENABLE_I2C4       0
#define BSPCFG_ENABLE_II2C4      0
#define BSPCFG_ENABLE_SPI1       0
#define BSPCFG_ENABLE_SPI2       0
#define BSPCFG_ENABLE_SPI3       0
#define BSPCFG_ENABLE_SPI4       0
#define BSPCFG_ENABLE_SPI5       1
#define BSPCFG_ENABLE_RTCDEV     0
#define BSPCFG_ENABLE_ADC1       0
#define BSPCFG_ENABLE_ADC2       0
#define BSPCFG_ENABLE_IODEBUG    0

/* don't support uncached memory */
#define MQX_USE_UNCACHED_MEM     0

#define MQX_USE_LWMEM_ALLOCATOR  0

/* no sram pool, instead, SRAM region in link script is used to extend the system pool */
#define BSPCFG_HAS_SRAM_POOL     0

#define MQX_USE_IDLE_TASK               1
#define MQX_ENABLE_LOW_POWER            1
#define MQXCFG_ENABLE_FP                1
#define MQX_INCLUDE_FLOATING_POINT_IO   0

#define MQX_IS_MULTI_PROCESSOR          1
#define MQX_USE_IPC                     0

#define MQX_TASK_DESTRUCTION     1

#define MQX_USE_TIMER            1

#define BSPCFG_CLK_DETAIL_LOGS              0
/*
 * Before Linux and MQX get a mechanism on share clock nodes manipulation, a
 * walkaround is needed to prevent each peer from manually physcially close
 * any clock nodes. The mechanism is to set every node's inital "is_always_open"
 * as 1. This macro is used to turn on this walkaround
 */
// by fefr, if = 0 i2c not work fine !!!
#define BSPCFG_CM_LINUX_PEER_WALKAROUND		1

#define MQX_ENABLE_MCORE_LPM                1

/* use the rest of defaults from small-RAM-device profile */
#include "small_ram_config.h"

/* and enable verification checks in kernel */
#include "verif_enabled_config.h"

#endif /* __user_config_h__ */
