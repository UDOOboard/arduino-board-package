#ifndef __mma8451q_lapo_h__
#define __mma8451q_lapo_h__
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
* FileName: mma8451q_lapo.h
* Version :
* Date    : May-16-2014
*
* Comments:
*
*   MMA8451Q Portrait/Landscape detection interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mma8451q_reg.h"

// Portrait/Landscape detection useful macro

// Debounce counter mode macro
#define MMA8451Q_PL_CFG_DBCNTM_DECREMENT              0x00
#define MMA8451Q_PL_CFG_DBCNTM_CLEAR                  MMA8451Q_PL_CFG_DBCNTM_MASK

// Back/Front Trip Angle Threshold macro
#define MMA8451Q_PL_BACK_FRONT_THRESHOLD_65_DEGREE    0x00
#define MMA8451Q_PL_BACK_FRONT_THRESHOLD_70_DEGREE    0x40
#define MMA8451Q_PL_BACK_FRONT_THRESHOLD_75_DEGREE    0x80
#define MMA8451Q_PL_BACK_FRONT_THRESHOLD_80_DEGREE    0xC0

// Portrait/Landscape Threshold macro
#define MMA8451Q_PL_THRESHOLD_15_DEGREE               (0x07 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_20_DEGREE               (0x09 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_30_DEGREE               (0x0C << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_35_DEGREE               (0x0D << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_40_DEGREE               (0x0F << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_45_DEGREE               (0x10 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_55_DEGREE               (0x13 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_60_DEGREE               (0x14 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_70_DEGREE               (0x17 << MMA8451Q_P_L_THS_REG_THS_SHIFT)
#define MMA8451Q_PL_THRESHOLD_75_DEGREE               (0x19 << MMA8451Q_P_L_THS_REG_THS_SHIFT)

// Z-Lock Angle Threshold macro
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_14_DEGREE        0x00
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_18_DEGREE        0x01
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_21_DEGREE        0x02
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_25_DEGREE        0x03
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_29_DEGREE        0x04
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_33_DEGREE        0x05
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_37_DEGREE        0x06
#define MMA8451Q_PL_Z_LOCK_THRESHOLD_42_DEGREE        0x07

// Hysteresis of Portrait/Landscape trip macro
#define MMA8451Q_PL_HYSTERESIS_0_DEGREE               0x00
#define MMA8451Q_PL_HYSTERESIS_4_DEGREE               0x01
#define MMA8451Q_PL_HYSTERESIS_7_DEGREE               0x02
#define MMA8451Q_PL_HYSTERESIS_11_DEGREE              0x03
#define MMA8451Q_PL_HYSTERESIS_14_DEGREE              0x04
#define MMA8451Q_PL_HYSTERESIS_17_DEGREE              0x05
#define MMA8451Q_PL_HYSTERESIS_21_DEGREE              0x06
#define MMA8451Q_PL_HYSTERESIS_24_DEGREE              0x07

// Portrait/Landscape function enable macro
#define MMA8451Q_PL_DISABLE                           0x00
#define MMA8451Q_PL_ENABLE                            MMA8451Q_PL_CFG_PL_EN_MASK

// Portrait/Landscape status macro
#define MMA8451Q_PL_STATUS_NEWLP                      MMA8451Q_PL_STATUS_NEWLP_MASK
#define MMA8451Q_PL_STATUS_LO                         MMA8451Q_PL_STATUS_LO_MASK
#define MMA8451Q_PL_STATUS_LAPO                       MMA8451Q_PL_STATUS_LAPO_MASK
#define MMA8451Q_PL_STATUS_PU                         0x00
#define MMA8451Q_PL_STATUS_PD                         0x02
#define MMA8451Q_PL_STATUS_LR                         0x04
#define MMA8451Q_PL_STATUS_LL                         0x06
#define MMA8451Q_PL_STATUS_BAFRO                      MMA8451Q_PL_STATUS_BAFRO_MASK
#define MMA8451Q_PL_STATUS_FRONT                      0x00
#define MMA8451Q_PL_STATUS_BACK                       MMA8451Q_PL_STATUS_BAFRO_MASK

/* Function Prototype */

bool mma8451q_set_lapo_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_mode                              /* Lapo function debounce counter enable config */
);

bool mma8451q_get_lapo_db_cnt_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store debounce counter enable config */
);

bool mma8451q_set_lapo_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     cnt_value                             /* Lapo function debounce counter to be set */
);

bool mma8451q_get_lapo_db_cnt
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store debounce counter value */
);

bool mma8451q_set_back_front_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold                             /* Threshold of back/front trip angle */
);

bool mma8451q_get_back_front_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store back front threshold */
);

bool mma8451q_set_lapo_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold                             /* Threshold of Portrait/Landscape trip angle */
);

bool mma8451q_get_lapo_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store threshold of Portrait/Landscape trip angle */
);

bool mma8451q_set_z_lock_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     threshold                             /* Threshold of z-lock angle */
);

bool mma8451q_get_z_lock_threshold
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store threshold of z-lock angle */
);

bool mma8451q_set_lapo_trip_hys
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     hysteresis                            /* Hysteresis of Portrait/Landscape trip */
);

bool mma8451q_get_lapo_trip_hys
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store hysteresis of Portrait/Landscape trip */
);

bool mma8451q_set_lapo_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     lapo_enabled                          /* Portrait/Landscape function enable config */
);

bool mma8451q_get_lapo_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Portrait/Landscape function enable config */
);

bool mma8451q_get_lapo_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Portrait/Landscape function status */
);

#endif
