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
*   This file contains the type definitions for the i.MX microcontrollers.
*
*
*END************************************************************************/

#ifndef __imx6sx_h__
#define __imx6sx_h__

#define _imx6sx_h_version "$Version:1.0.0.0$"
#define _imx6sx_h_date    "$Date:Feb-07-2014$"

/**************************************************************************
 TEMPORARY CPU HEADERS
**************************************************************************/
#ifndef __ASM__
#include <stdint.h>


#if (MQX_CPU == PSP_CPU_IMX6SX_M4)

  #include "iMX6SX.h"
  #include <nvic.h>

#else
    #error "Ooooo, too new cpu..."
#endif

#endif // __ASM__


/*
*******************************************************************************
**
**                  CONSTANT DEFINITIONS
**
*******************************************************************************
*/
#define PSP_NUM_CORES                   2
#define SEMA4_NUM_DEVICES               1

#if (MQX_CPU == PSP_CPU_IMX6SX_M4)
    #ifndef PSP_HAS_CODE_CACHE
    #define PSP_HAS_CODE_CACHE          1
    #endif

    #ifndef PSP_HAS_DATA_CACHE
    #define PSP_HAS_DATA_CACHE          1
    #endif

    #ifndef PSP_HAS_FPU
    #define PSP_HAS_FPU       	        1
    #endif
#endif

#ifndef __ASM__

/* Standard cache macros */
#if PSP_HAS_DATA_CACHE
#define _DCACHE_ENABLE(n)               _dcache_enable()
#define _DCACHE_DISABLE()               _dcache_disable()
#define _DCACHE_FLUSH()                 _dcache_flush()
#define _DCACHE_FLUSH_LINE(p)           _dcache_flush_line(p)
#define _DCACHE_FLUSH_MLINES(p, m)      _dcache_flush_mlines(p,m)
#define _DCACHE_INVALIDATE()            _dcache_invalidate()
#define _DCACHE_INVALIDATE_LINE(p)      _dcache_invalidate_line(p)
#define _DCACHE_INVALIDATE_MLINES(p, m) _dcache_invalidate_mlines(p, m)

#define _DCACHE_FLUSH_MBYTES(p, m)      _DCACHE_FLUSH_MLINES(p, m)
#define _DCACHE_INVALIDATE_MBYTES(p, m) _DCACHE_INVALIDATE_MLINES(p, m)

#else
#define _DCACHE_ENABLE(n)
#define _DCACHE_DISABLE()
#define _DCACHE_FLUSH()
#define _DCACHE_FLUSH_LINE(p)
#define _DCACHE_FLUSH_MLINES(p, m)
#define _DCACHE_INVALIDATE()
#define _DCACHE_INVALIDATE_LINE(p)
#define _DCACHE_INVALIDATE_MLINES(p, m)

#define _DCACHE_FLUSH_MBYTES(p, m)
#define _DCACHE_INVALIDATE_MBYTES(p, m)
#endif

#if PSP_HAS_CODE_CACHE
#define _ICACHE_ENABLE(n)                   _icache_enable()
#define _ICACHE_DISABLE()                   _icache_disable()
#define _ICACHE_INVALIDATE()                _icache_invalidate()
#define _ICACHE_INVALIDATE_LINE(p)          _icache_invalidate_line(p)
#define _ICACHE_INVALIDATE_MLINES(p, m)     _icache_invalidate_mlines(p, m)
#else
#define _ICACHE_ENABLE(n)
#define _ICACHE_DISABLE()
#define _ICACHE_FLUSH()
#define _ICACHE_FLUSH_LINE(p)
#define _ICACHE_FLUSH_MLINES(p, m)
#define _ICACHE_INVALIDATE()
#define _ICACHE_INVALIDATE_LINE(p)
#define _ICACHE_INVALIDATE_MLINES(p, m)
#endif

/*
 * Sleep function definition.
 */
#if PSP_BYPASS_P3_WFI
#define _ASM_SLEEP(param)    {extern void(*_sleep_p3_ram)(uint32_t*);_sleep_p3_ram(param);}
#else
#define _ASM_SLEEP(param)    _ASM_WFI()
#endif

typedef uint32_t PSP_INTERRUPT_TABLE_INDEX;
typedef void (*vector_entry)(void);

#endif // __ASM__
/**************************************************************************
**************************************************************************/

/*------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/* A5 L1 and L2 caches, M4 cache have 32-byte lines. */
#define PSP_CACHE_LINE_SIZE          32
#define PSP_CACHE_LINE_ALIGNMENT    (-PSP_CACHE_LINE_SIZE)

#ifndef __ASM__



/*------------------------------------------------------------------------*/
/*
**                      TYPE DEFINITIONS
*/
/*------------------------------------------------------------------------*/
/*
**                      FUNCTION PROTOTYPES AND GLOBAL EXTERNS
*/

#ifdef __cplusplus
extern "C" {
#endif

/* PSP Cache prototypes */
void _dcache_enable(void);
void _dcache_disable(void);
void _dcache_flush(void);
void _dcache_flush_line(void *);
void _dcache_flush_mlines(void *, uint32_t);
void _dcache_invalidate(void);
void _dcache_invalidate_line(void *);
void _dcache_invalidate_mlines(void *, uint32_t);

void _icache_enable(void);
void _icache_disable(void);
void _icache_flush(void);
void _icache_flush_line(void *);
void _icache_flush_mlines(void *, uint32_t);
void _icache_invalidate(void);
void _icache_invalidate_line(void *);
void _icache_invalidate_mlines(void *, uint32_t);

#ifdef __cplusplus
}
#endif

#endif /* __ASM__ */

#endif // __imx6sx_h__
