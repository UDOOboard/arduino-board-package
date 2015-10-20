
/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
*
* SPDX-License-Identifier: BSD-3-Clause
* The BSD-3-Clause License for this file can be found in the COPYING.BSD file 
* included with this distribution or at 
* http://opensource.org/licenses/BSD-3-Clause
*****************************************************************************
*
* Comments:
*
*   This file contains function prototypes for i.MX6SX-specific 
*   MCC library functions
*
*END************************************************************************/

#ifndef __mcc_pele_h__
#define __mcc_pele_h__

#define MCC_VECTOR_NUMBER_INVALID     (0)

unsigned int mcc_get_cpu_to_cpu_vector(unsigned int);
void mcc_enable_cpu_to_cpu_interrupt(unsigned int);
void mcc_clear_cpu_to_cpu_interrupt(unsigned int);
void mcc_triger_cpu_to_cpu_interrupt(void);

#define MU_GP_M4_INDEX 3

#endif // __filename_h__

