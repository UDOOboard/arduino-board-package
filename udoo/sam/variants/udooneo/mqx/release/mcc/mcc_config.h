
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
*   This is the main MCC configuration file
*
*
*END************************************************************************/

#ifndef __MCC_CONFIG__
#define __MCC_CONFIG__

/* used OS */
#define MCC_OS_USED                    (MCC_MQX)

/* base address of shared memory */
#define MCC_BASE_ADDRESS               (BSP_SHARED_RAM_START)

/* size (in bytes) and number of receive buffers */
#define MCC_ATTR_NUM_RECEIVE_BUFFERS   (10)
#define MCC_ATTR_BUFFER_SIZE_IN_BYTES  (1024)

/* maximum number of receive endpoints (application specific setting),
 * do not assign it to a value greater than 255 ! */
#define MCC_ATTR_MAX_RECEIVE_ENDPOINTS (5)

/* size of the signal queue */
#define MCC_MAX_OUTSTANDING_SIGNALS    (10)

/* number of cores */
#define MCC_NUM_CORES                  (2)

/* core number */
#define MCC_CORE_NUMBER                (_psp_core_num())

/* semaphore number */
#define MCC_SHMEM_SEMAPHORE_NUMBER      (1)
#define MCC_PRINTF_SEMAPHORE_NUMBER     (2)
#define MCC_I2C_SEMAPHORE_NUMBER        (3)
#define MCC_RESERVED1_SEMAPHORE_NUMBER  (4)
#define MCC_RESERVED2_SEMAPHORE_NUMBER  (5)

/* data non-copy mechanisms enabled  */
#define MCC_SEND_RECV_NOCOPY_API_ENABLED (1)

#endif /* __MCC_CONFIG__ */
