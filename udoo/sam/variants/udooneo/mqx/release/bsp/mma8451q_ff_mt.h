#ifndef __mma8451q_ff_mt_h__
#define __mma8451q_ff_mt_h__
/**HEADER*******************************************************************
*
* Copyright (c) 2014 Freescale Semiconductor;
* All Rights Reserved
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
**************************************************************************
*
* FileName: mma8451q_ff_mt.h
* Version :
* Date    : May-16-2014
*
* Comments:
*
*   MMA8451Q Motion and Freefall detection interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mma8451q_reg.h"

// Motion and Freefall detection useful macro

// Debounce counter mode macro
#define MMA8451Q_FF_MT_CFG_DBCNTM_DECREMENT           0x00
#define MMA8451Q_FF_MT_CFG_DBCNTM_CLEAR               MMA8451Q_FF_MT_THS_DBCNTM_MASK

// Event Latch Enable macro
#define MMA8451Q_FF_MT_CFG_ELE_DISABLE                0x00
#define MMA8451Q_FF_MT_CFG_ELE_ENABLE                 MMA8451Q_FF_MT_CFG_ELE_MASK

// Freefall & motion detection selection macro
#define MMA8451Q_FF_MT_SELECT_FREEFALL                0x00
#define MMA8451Q_FF_MT_SELECT_MOTION                  MMA8451Q_FF_MT_CFG_OAE_MASK

// Freefall & motion detection enable macro
#define MMA8451Q_FF_MT_ENABLE_Z                       MMA8451Q_FF_MT_CFG_ZEFE_MASK
#define MMA8451Q_FF_MT_DISABLE_Z                      0x00
#define MMA8451Q_FF_MT_ENABLE_Y                       MMA8451Q_FF_MT_CFG_YEFE_MASK
#define MMA8451Q_FF_MT_DISABLE_Y                      0x00
#define MMA8451Q_FF_MT_ENABLE_X                       MMA8451Q_FF_MT_CFG_XEFE_MASK
#define MMA8451Q_FF_MT_DISABLE_X                      0x00

// Freefall & Motion Status macro
#define MMA8451Q_FF_MT_EVENT_ACTIVE                   MMA8451Q_FF_MT_SRC_EA_MASK
#define MMA8451Q_FF_MT_EVENT_Z_DETECT                 MMA8451Q_FF_MT_SRC_ZHE_MASK
#define MMA8451Q_FF_MT_EVENT_Y_DETECT                 MMA8451Q_FF_MT_SRC_YHE_MASK
#define MMA8451Q_FF_MT_EVENT_X_DETECT                 MMA8451Q_FF_MT_SRC_XHE_MASK
#define MMA8451Q_FF_MT_EVENT_Z_POSITIVE               0x00
#define MMA8451Q_FF_MT_EVENT_Z_NEGATIVE               MMA8451Q_FF_MT_SRC_ZHP_MASK
#define MMA8451Q_FF_MT_EVENT_Y_POSITIVE               0x00
#define MMA8451Q_FF_MT_EVENT_Y_NEGATIVE               MMA8451Q_FF_MT_SRC_YHP_MASK
#define MMA8451Q_FF_MT_EVENT_X_POSITIVE               0x00
#define MMA8451Q_FF_MT_EVENT_X_NEGATIVE               MMA8451Q_FF_MT_SRC_XHP_MASK

bool mma8451q_set_ff_mt_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_mode                              /* Free Fall/Motion function debounce counter enable config */
);

bool mma8451q_get_ff_mt_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store debounce counter enable config */
);

bool mma8451q_set_ff_mt_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_value                             /* Free Fall/Motion function debounce counter value */
);

bool mma8451q_get_ff_mt_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function debounce counter value */
);

bool mma8451q_set_ff_mt_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold                             /* Free Fall/Motion function threshold */
);

bool mma8451q_get_ff_mt_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function threshold */
);

bool mma8451q_set_ff_mt_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     latch_enable                          /* Free Fall/Motion function event latch state */
);

bool mma8451q_get_ff_mt_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function event latch state */
);

bool mma8451q_set_ff_mt_selection
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     selection                             /* Free Fall/Motion function selection */
);

bool mma8451q_get_ff_mt_selection
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function selection */
);

bool mma8451q_set_ff_mt_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     enable_state                          /* Free Fall/Motion function enable state to be set */
);

bool mma8451q_get_ff_mt_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function enable state */
);

bool mma8451q_get_ff_mt_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Free Fall/Motion function status */
);

#endif
