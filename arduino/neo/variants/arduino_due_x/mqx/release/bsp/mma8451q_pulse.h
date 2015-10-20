#ifndef __mma8451q_pulse_h__
#define __mma8451q_pulse_h__
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
* FileName: mma8451q_pulse.h
* Version :
* Date    : May-16-2014
*
* Comments:
*
*   MMA8451Q pulse detection interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mma8451q_reg.h"

// Transient detection useful macro

// Axis define
#define MMA8451Q_PULSE_AXIS_X                         0x01
#define MMA8451Q_PULSE_AXIS_Y                         0x02
#define MMA8451Q_PULSE_AXIS_Z                         0x03

// Double Pulse Abort macro
#define MMA8451Q_PULSE_CFG_DPA_DISABLE                0x00
#define MMA8451Q_PULSE_CFG_DPA_ENABLE                 MMA8451Q_PULSE_CFG_DPA_MASK

// Event Latch Enable macro
#define MMA8451Q_PULSE_CFG_ELE_DISABLE                0x00
#define MMA8451Q_PULSE_CFG_ELE_ENABLE                 MMA8451Q_PULSE_CFG_ELE_MASK

// High pass filter macro
#define MMA8451Q_PULSE_HIGH_PASS_FILTER_DISABLE       0x00
#define MMA8451Q_PULSE_HIGH_PASS_FILTER_ENABLE        MMA8451Q_HP_FILTER_CUTOFF_P_HPF_BYP_MASK

// Low pass filter macro
#define MMA8451Q_PULSE_LOW_PASS_FILTER_DISABLE        0x00
#define MMA8451Q_PULSE_LOW_PASS_FILTER_ENABLE         MMA8451Q_HP_FILTER_CUTOFF_P_LPF_EN_MASK

// Tap detection enable macro
#define MMA8451Q_SINGLE_PULSE_ENABLE_Z                MMA8451Q_PULSE_CFG_ZSPEFE_MASK
#define MMA8451Q_SINGLE_PULSE_DISABLE_Z               0x00
#define MMA8451Q_SINGLE_PULSE_ENABLE_Y                MMA8451Q_PULSE_CFG_YSPEFE_MASK
#define MMA8451Q_SINGLE_PULSE_DISABLE_Y               0x00
#define MMA8451Q_SINGLE_PULSE_ENABLE_X                MMA8451Q_PULSE_CFG_XSPEFE_MASK
#define MMA8451Q_SINGLE_PULSE_DISABLE_X               0x00

#define MMA8451Q_DOUBLE_PULSE_ENABLE_Z                MMA8451Q_PULSE_CFG_ZDPEFE_MASK
#define MMA8451Q_DOUBLE_PULSE_DISABLE_Z               0x00
#define MMA8451Q_DOUBLE_PULSE_ENABLE_Y                MMA8451Q_PULSE_CFG_YDPEFE_MASK
#define MMA8451Q_DOUBLE_PULSE_DISABLE_Y               0x00
#define MMA8451Q_DOUBLE_PULSE_ENABLE_X                MMA8451Q_PULSE_CFG_XDPEFE_MASK
#define MMA8451Q_DOUBLE_PULSE_DISABLE_X               0x00

// Pulse Event Status macro
#define MMA8451Q_PULSE_EVENT_ACTIVE                   MMA8451Q_PULSE_SRC_EA_MASK
#define MMA8451Q_PULSE_EVENT_Z_DETECT                 MMA8451Q_PULSE_SRC_AXZ_MASK
#define MMA8451Q_PULSE_EVENT_Y_DETECT                 MMA8451Q_PULSE_SRC_AXY_MASK
#define MMA8451Q_PULSE_EVENT_X_DETECT                 MMA8451Q_PULSE_SRC_AXX_MASK
#define MMA8451Q_DOUBLE_PULSE_EVENT_DETECT            MMA8451Q_PULSE_SRC_DPE_MASK

#define MMA8451Q_PULSE_EVENT_Z_POSITIVE               0x00
#define MMA8451Q_PULSE_EVENT_Z_NEGATIVE               MMA8451Q_PULSE_SRC_POL_Z_MASK
#define MMA8451Q_PULSE_EVENT_Y_POSITIVE               0x00
#define MMA8451Q_PULSE_EVENT_Y_NEGATIVE               MMA8451Q_PULSE_SRC_POL_Y_MASK
#define MMA8451Q_PULSE_EVENT_X_POSITIVE               0x00
#define MMA8451Q_PULSE_EVENT_X_NEGATIVE               MMA8451Q_PULSE_SRC_POL_X_MASK

bool mma8451q_set_double_pulse_abort
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     abort_sel                             /* Pulse detect function double pulse abort selection */
);

bool mma8451q_get_double_pulse_abort
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store double pulse abort selection */
);

bool mma8451q_set_pulse_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold,                            /* Pulse detect function threshold in single axis */
    uint8_t     axis                                  /* Axis selection with mask */
);

bool mma8451q_get_pulse_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer,                               /* Buffer to store pulse detect function threshold in single axis */
    uint8_t     axis                                  /* Axis selection with mask */
);

bool mma8451q_set_pulse_time_limit
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     time_limit                            /* Pulse detect function time limit */
);

bool mma8451q_get_pulse_time_limit
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect function time limit */
);

bool mma8451q_set_pulse_latency
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     latency                               /* Pulse detect function latency */
);

bool mma8451q_get_pulse_latency
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect function latency */
);

bool mma8451q_set_pulse_time_window
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     time_window                           /* Pulse detect function time window */
);

bool mma8451q_get_pulse_time_window
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect function time window */
);

bool mma8451q_set_pulse_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     latch_state                           /* Pulse detect function event latch_state */
);

bool mma8451q_get_pulse_event_latch_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect function event latch_state */
);

bool mma8451q_set_pulse_hpf_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     bypass_state                          /* Pulse detect function high pass filter bypass state */
);

bool mma8451q_get_pulse_hpf_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect high pass filter bypass state */
);

bool mma8451q_set_pulse_lpf_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     bypass_state                          /* Pulse detect function low pass filter bypass state */
);

bool mma8451q_get_pulse_lpf_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect low pass filter bypass state */
);

bool mma8451q_set_pulse_detect_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     tap_state                             /* Pulse detect function enable state to be set */
);

bool mma8451q_get_pulse_detect_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect function enable state */
);

bool mma8451q_get_pulse_detect_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store pulse detect status */
);

#endif
