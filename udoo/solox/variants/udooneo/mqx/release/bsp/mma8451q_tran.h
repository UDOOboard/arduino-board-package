#ifndef __mma8451q_tran_h__
#define __mma8451q_tran_h__
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
* FileName: mma8451q_tran.h
* Version :
* Date    : May-16-2014
*
* Comments:
*
*   MMA8451Q transient detection interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mma8451q_reg.h"

// Transient detection useful macro

// Debounce counter mode macro
#define MMA8451Q_TRANSIENT_CFG_DBCNTM_DECREMENT       0x00
#define MMA8451Q_TRANSIENT_CFG_DBCNTM_CLEAR           MMA8451Q_TRANSIENT_THS_DBCNTM_MASK

// Event Latch Enable macro
#define MMA8451Q_TRANSIENT_CFG_ELE_DISABLE            0x00
#define MMA8451Q_TRANSIENT_CFG_ELE_ENABLE             MMA8451Q_TRANSIENT_CFG_ELE_MASK

// Bypass High-Pass filter macro
#define MMA8451Q_TRANSIENT_CFG_HPF_ENABLE             0x00
#define MMA8451Q_TRANSIENT_CFG_HPF_DISABLE            MMA8451Q_TRANSIENT_CFG_HPF_BYP_MASK

// Transient detection enable macro
#define MMA8451Q_TRANSIENT_ENABLE_Z                   MMA8451Q_TRANSIENT_CFG_ZTEFE_MASK
#define MMA8451Q_TRANSIENT_DISABLE_Z                  0x00
#define MMA8451Q_TRANSIENT_ENABLE_Y                   MMA8451Q_TRANSIENT_CFG_YTEFE_MASK
#define MMA8451Q_TRANSIENT_DISABLE_Y                  0x00
#define MMA8451Q_TRANSIENT_ENABLE_X                   MMA8451Q_TRANSIENT_CFG_XTEFE_MASK
#define MMA8451Q_TRANSIENT_DISABLE_X                  0x00

// Transient Status macro
#define MMA8451Q_TRANSIENT_EVENT_ACTIVE               MMA8451Q_TRANSIENT_SRC_EA_MASK
#define MMA8451Q_TRANSIENT_EVENT_Z_DETECT             MMA8451Q_TRANSIENT_SRC_Z_MASK
#define MMA8451Q_TRANSIENT_EVENT_Y_DETECT             MMA8451Q_TRANSIENT_SRC_Y_MASK
#define MMA8451Q_TRANSIENT_EVENT_X_DETECT             MMA8451Q_TRANSIENT_SRC_X_MASK
#define MMA8451Q_TRANSIENT_EVENT_Z_POSITIVE           0x00
#define MMA8451Q_TRANSIENT_EVENT_Z_NEGATIVE           MMA8451Q_TRANSIENT_SRC_Z_POL_MASK
#define MMA8451Q_TRANSIENT_EVENT_Y_POSITIVE           0x00
#define MMA8451Q_TRANSIENT_EVENT_Y_NEGATIVE           MMA8451Q_TRANSIENT_SRC_Y_POL_MASK
#define MMA8451Q_TRANSIENT_EVENT_X_POSITIVE           0x00
#define MMA8451Q_TRANSIENT_EVENT_X_NEGATIVE           MMA8451Q_TRANSIENT_SRC_X_POL_MASK

bool mma8451q_set_transient_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_mode                              /* Transient detect function debounce counter enable config */
);

bool mma8451q_get_transient_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store debounce counter enable config */
);

bool mma8451q_set_transient_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_value                             /* Transient detect function debounce counter value */
);

bool mma8451q_get_transient_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store debounce counter value */
);

bool mma8451q_set_transient_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold                             /* Transient detect function threshold */
);

bool mma8451q_get_transient_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store transient detect function threshold */
);

bool mma8451q_set_transient_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     latch_state                           /* Transient detect function event latch state */
);

bool mma8451q_get_transient_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store transient detect function event latch state */
);

bool mma8451q_set_transient_bypass_hpf
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     bypass_state                          /* Transient detect function high pass filter bypass state */
);

bool mma8451q_get_transient_bypass_hpf
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store transient detect high pass filter bypass state */
);

bool mma8451q_set_transient_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     enable_state                          /* Transient detect function enable config */
);

bool mma8451q_get_transient_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store transient detect function enable state */
);

bool mma8451q_get_transient_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store transient detect function status */
);

#endif
