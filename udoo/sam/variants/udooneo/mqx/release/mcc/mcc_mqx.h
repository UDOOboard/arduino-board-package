
/*HEADER**********************************************************************
*
* Copyright 2013-2014 Freescale Semiconductor, Inc.
* 
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause License for this file can be found in the COPYING.BSD file 
* included with this distribution or at 
* http://opensource.org/licenses/BSD-3-Clause
*****************************************************************************
*
* Comments:
*
*   This file contains prototypes for MQX-specific MCC library functions
*
*
*END************************************************************************/

#ifndef __MCC_MQX__
#define __MCC_MQX__

#include <mqx.h>
#include <bsp.h>
#include <lwevent.h>
#include "core_mutex.h"
#include "mcc_config.h"
#include "mcc_common.h"
#include "mcc_api.h"

#if (MQX_CPU == PSP_CPU_VF65GS10_A5) || (MQX_CPU == PSP_CPU_VF65GS10_M4)
#include "vybrid.h"
#elif (MQX_CPU == PSP_CPU_IMX6SX_M4)
#include "imx.h"
#endif

#define MCC_MQX_LWEVENT_COMPONENTS_COUNT   (8)
#define MCC_MQX_LWEVENT_GROUP_SIZE         (32)

#define MCC_NODE_NUMBER                    (0)

#define MCC_DCACHE_ENABLE(n)               _DCACHE_ENABLE(n)
#define MCC_DCACHE_DISABLE()               _DCACHE_DISABLE()
#define MCC_DCACHE_FLUSH()                 _DCACHE_FLUSH()
#define MCC_DCACHE_FLUSH_LINE(p)           _DCACHE_FLUSH_LINE(p)
#define MCC_DCACHE_FLUSH_MLINES(p, m)      _DCACHE_FLUSH_MLINES(p, m)
#define MCC_DCACHE_INVALIDATE()            _DCACHE_INVALIDATE()
#define MCC_DCACHE_INVALIDATE_LINE(p)      _DCACHE_INVALIDATE_LINE(p)
#define MCC_DCACHE_INVALIDATE_MLINES(p, m) _DCACHE_INVALIDATE_MLINES(p, m)

#define MCC_MEM_VIRT_TO_PHYS(a)            (a)
#define MCC_MEM_PHYS_TO_VIRT(a)            (a)

/* Semaphore-related functions */
int mcc_init_semaphore(unsigned int);
int mcc_deinit_semaphore(unsigned int);
int mcc_get_semaphore(void);
int mcc_release_semaphore(void);

/* CPU-to-CPU interrupt-related functions */
int mcc_register_cpu_to_cpu_isr(void);
int mcc_generate_cpu_to_cpu_interrupt(void);

/* Memory management-related functions */
void mcc_memcpy(void*, void*, unsigned int);

int mcc_init_os_sync(void);
int mcc_deinit_os_sync(void);
void mcc_clear_os_sync_for_ep(MCC_ENDPOINT *);
int mcc_wait_for_buffer_freed(MCC_RECEIVE_BUFFER **, unsigned int);
int mcc_wait_for_buffer_queued(MCC_ENDPOINT *, unsigned int);

MCC_BOOKEEPING_STRUCT *mcc_get_bookeeping_data(void);
#endif /* __MCC_MQX__ */
