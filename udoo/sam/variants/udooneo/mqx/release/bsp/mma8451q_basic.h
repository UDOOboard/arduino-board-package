#ifndef __mma8451q_basic_h__
#define __mma8451q_basic_h__
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
* FileName: mma8451q_basic.h
* Version :
* Date    : May-5-2014
*
* Comments:
*
*   MMA8451Q basic IO interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mqx.h"

#include "mma8451q_reg.h"

/* Useful macros */

// Data ready status macro
#define MMA8451Q_DATA_READY_ZYXOW                           MMA8451Q_STATUS_ZYXOW_MASK
#define MMA8451Q_DATA_READY_ZOW                             MMA8451Q_STATUS_ZOW_MASK
#define MMA8451Q_DATA_READY_YOW                             MMA8451Q_STATUS_YOW_MASK
#define MMA8451Q_DATA_READY_XOW                             MMA8451Q_STATUS_XOW_MASK
#define MMA8451Q_DATA_READY_ZYXDR                           MMA8451Q_STATUS_ZYXDR_MASK
#define MMA8451Q_DATA_READY_ZDR                             MMA8451Q_STATUS_ZDR_MASK
#define MMA8451Q_DATA_READY_YDR                             MMA8451Q_STATUS_YDR_MASK
#define MMA8451Q_DATA_READY_XDR                             MMA8451Q_STATUS_XDR_MASK

// System mode macro
#define MMA8451Q_SYSMOD_STANDBY                             0x00
#define MMA8451Q_SYSMOD_WAKE                                0x01
#define MMA8451Q_SYSMOD_SLEEP                               0x02

// Output data rate macro
#define MMA8451Q_OUTPUT_DATA_RATE_800HZ                     0x00
#define MMA8451Q_OUTPUT_DATA_RATE_400HZ                     0x08
#define MMA8451Q_OUTPUT_DATA_RATE_200HZ                     0x10
#define MMA8451Q_OUTPUT_DATA_RATE_100HZ                     0x18
#define MMA8451Q_OUTPUT_DATA_RATE_50HZ                      0x20
#define MMA8451Q_OUTPUT_DATA_RATE_12HZ5                     0x28
#define MMA8451Q_OUTPUT_DATA_RATE_6HZ25                     0x30
#define MMA8451Q_OUTPUT_DATA_RATE_1HZ56                     0x38

// Active power scheme macro
#define MMA8451Q_ACTIVE_POWER_SCHEME_NORMAL                 0x00
#define MMA8451Q_ACTIVE_POWER_SCHEME_LOW_NOISE_LOW_POWER    0x01
#define MMA8451Q_ACTIVE_POWER_SCHEME_HIGH_RESOLUTION        0x02
#define MMA8451Q_ACTIVE_POWER_SCHEME_LOW_POWER              0x03

// Full scale range macro
#define MMA8451Q_FULL_SCALE_RANGE_2G                        0x00
#define MMA8451Q_FULL_SCALE_RANGE_4G                        0x01
#define MMA8451Q_FULL_SCALE_RANGE_8G                        0x02

// Burst read mode macro
#define MMA8451Q_BURST_READ_MODE_NORMAL                     0x00
#define MMA8451Q_BURST_READ_MODE_FAST                       MMA8451Q_CTRL_REG1_F_READ_MASK

// Self test state macro
#define MMA8451Q_SELF_TEST_DISABLE                          0x00
#define MMA8451Q_SELF_TEST_ENABLE                           MMA8451Q_CTRL_REG2_ST_MASK

// Sensor reset status macro
#define MMA8451Q_SENOR_RESET_STATUS                         MMA8451Q_CTRL_REG2_RST_MASK

// Operating mode macro
#define MMA8451Q_OPERATING_MODE_STANDBY                     0x00
#define MMA8451Q_OPERATING_MODE_ACTIVE                      MMA8451Q_CTRL_REG1_ACTIVE_MASK

// FIFO Mode macro
#define MMA8451Q_FIFO_MODE_DISABLE                          0x00
#define MMA8451Q_FIFO_MODE_CIRCULAR                         0x40
#define MMA8451Q_FIFO_MODE_FULL_FILL                        0x80
#define MMA8451Q_FIFO_MODE_TRIGGER                          0xC0

// FIFO trigger configuration macro
#define MMA8451Q_TRIG_CFG_TRANS                             MMA8451Q_TRIG_CFG_TRANS_MASK
#define MMA8451Q_TRIG_CFG_LNDPRT                            MMA8451Q_TRIG_CFG_LNDPRT_MASK
#define MMA8451Q_TRIG_CFG_PULSE                             MMA8451Q_TRIG_CFG_PULSE_MASK
#define MMA8451Q_TRIG_CFG_FF_MT                             MMA8451Q_TRIG_CFG_FF_MT_MASK

// FIFO gate macro
#define MMA8451Q_FIFO_GATE_DISABLE                          0x00
#define MMA8451Q_FIFO_GATE_ENABLE                           MMA8451Q_CTRL_REG3_FIFO_GATE_MASK

// FIFO status macro
#define MMA8451Q_FIFO_EVENT_OVERFLOW                        MMA8451Q_F_STATUS_OVF_MASK
#define MMA8451Q_FIFO_EVENT_WATERMARK                       MMA8451Q_F_STATUS_WMRK_FLAG_MASK

// Interrupt polarity macro
#define MMA8451Q_INT_POLARITY_ACTIVE_LOW                    0x00
#define MMA8451Q_INT_POLARITY_ACTIVE_HIGH                   MMA8451Q_CTRL_REG3_IPOL_MASK

// Interrupt output mode macro
#define MMA8451Q_INT_MODE_PUSH_PULL                         0x00
#define MMA8451Q_INT_MODE_OPEN_DRAIN                        MMA8451Q_CTRL_REG3_PP_OD_MASK

// Interrupt pin route macro
#define MMA8451Q_ASLP_INT_ROUTE_TO_INT1                     MMA8451Q_CTRL_REG5_INT_CFG_ASLP_MASK
#define MMA8451Q_ASLP_INT_ROUTE_TO_INT2                     0x00
#define MMA8451Q_FIFO_INT_ROUTE_TO_INT1                     MMA8451Q_CTRL_REG5_INT_CFG_FIFO_MASK
#define MMA8451Q_FIFO_INT_ROUTE_TO_INT2                     0x00
#define MMA8451Q_TRANS_INT_ROUTE_TO_INT1                    MMA8451Q_CTRL_REG5_INT_CFG_TRANS_MASK
#define MMA8451Q_TRANS_INT_ROUTE_TO_INT2                    0x00
#define MMA8451Q_LNDPRT_INT_ROUTE_TO_INT1                   MMA8451Q_CTRL_REG5_INT_CFG_LNDPRT_MASK
#define MMA8451Q_LNDPRT_INT_ROUTE_TO_INT2                   0x00
#define MMA8451Q_PULSE_INT_ROUTE_TO_INT1                    MMA8451Q_CTRL_REG5_INT_CFG_PULSE_MASK
#define MMA8451Q_PULSE_INT_ROUTE_TO_INT2                    0x00
#define MMA8451Q_FF_MT_INT_ROUTE_TO_INT1                    MMA8451Q_CTRL_REG5_INT_CFG_FF_MT_MASK
#define MMA8451Q_FF_MT_INT_ROUTE_TO_INT2                    0x00
#define MMA8451Q_DRDY_INT_ROUTE_TO_INT1                     MMA8451Q_CTRL_REG5_INT_CFG_DRDY_MASK
#define MMA8451Q_DRDY_INT_ROUTE_TO_INT2                     0x00

// Interrupt Enable/Disable macro
#define MMA8451Q_ASLP_INT_ENABLE                            MMA8451Q_CTRL_REG4_INT_EN_ASLP_MASK
#define MMA8451Q_ASLP_INT_DISABLE                           0x00
#define MMA8451Q_FIFO_INT_ENABLE                            MMA8451Q_CTRL_REG4_INT_EN_FIFO_MASK
#define MMA8451Q_FIFO_INT_DISABLE                           0x00
#define MMA8451Q_TRANS_INT_ENABLE                           MMA8451Q_CTRL_REG4_INT_EN_TRANS_MASK
#define MMA8451Q_TRANS_INT_DISABLE                          0x00
#define MMA8451Q_LNDPRT_INT_ENABLE                          MMA8451Q_CTRL_REG4_INT_EN_LNDPR_MASK
#define MMA8451Q_LNDPRT_INT_DISABLE                         0x00
#define MMA8451Q_PULSE_INT_ENABLE                           MMA8451Q_CTRL_REG4_INT_EN_PULSE_MASK
#define MMA8451Q_PULSE_INT_DISABLE                          0x00
#define MMA8451Q_FF_MT_INT_ENABLE                           MMA8451Q_CTRL_REG4_INT_EN_FF_MT_MASK
#define MMA8451Q_FF_MT_INT_DISABLE                          0x00
#define MMA8451Q_DRDY_INT_ENABLE                            MMA8451Q_CTRL_REG4_INT_EN_DRDY_MASK
#define MMA8451Q_DRDY_INT_DISABLE                           0x00

// Interrupt source macro
#define MMA8451Q_INT_SOURCE_ASLP                            MMA8451Q_INT_SOURCE_ASLP_MASK
#define MMA8451Q_INT_SOURCE_FIFO                            MMA8451Q_INT_SOURCE_FIFO_MASK
#define MMA8451Q_INT_SOURCE_TRANS                           MMA8451Q_INT_SOURCE_TRANS_MASK
#define MMA8451Q_INT_SOURCE_LNDPRT                          MMA8451Q_INT_SOURCE_LNDPRT_MASK
#define MMA8451Q_INT_SOURCE_PULSE                           MMA8451Q_INT_SOURCE_PULSE_MASK
#define MMA8451Q_INT_SOURCE_FF_MT                           MMA8451Q_INT_SOURCE_FF_MT_MASK
#define MMA8451Q_INT_SOURCE_DRDY                            MMA8451Q_INT_SOURCE_DRDY_MASK

// Auto sleep output data rate macro
#define MMA8451Q_ASLP_OUTPUT_DATA_RATE_50HZ                 0x00
#define MMA8451Q_ASLP_OUTPUT_DATA_RATE_12HZ5                0x40
#define MMA8451Q_ASLP_OUTPUT_DATA_RATE_6HZ25                0x80
#define MMA8451Q_ASLP_OUTPUT_DATA_RATE_1HZ56                0xC0

// Auto sleep power scheme macro
#define MMA8451Q_ASLP_POWER_SCHEME_NORMAL                   0x00
#define MMA8451Q_ASLP_POWER_SCHEME_LOW_NOISE_LOW_POWER      0x08
#define MMA8451Q_ASLP_POWER_SCHEME_HIGH_RESOLUTION          0x10
#define MMA8451Q_ASLP_POWER_SCHEME_LOW_POWER                0x18

// Auto sleep Wake up source macro
#define MMA8451Q_ASLP_WAKE_TRANS_DISABLE                    0x00
#define MMA8451Q_ASLP_WAKE_TRANS_ENABLE                     MMA8451Q_CTRL_REG3_WAKE_TRANS_MASK
#define MMA8451Q_ASLP_WAKE_LNDPRT_DISABLE                   0x00
#define MMA8451Q_ASLP_WAKE_LNDPRT_ENABLE                    MMA8451Q_CTRL_REG3_WAKE_LNDPRT_MASK
#define MMA8451Q_ASLP_WAKE_PULSE_DISABLE                    0x00
#define MMA8451Q_ASLP_WAKE_PULSE_ENABLE                     MMA8451Q_CTRL_REG3_WAKE_PULSE_MASK
#define MMA8451Q_ASLP_WAKE_FF_MT_DISABLE                    0x00
#define MMA8451Q_ASLP_WAKE_FF_MT_ENABLE                     MMA8451Q_CTRL_REG3_WAKE_FF_MT_MASK

// AutoSleep state macro
#define MMA8451Q_AUTO_SLEEP_DISABLE                         0x00
#define MMA8451Q_AUTO_SLEEP_ENABLE                          MMA8451Q_CTRL_REG2_SLPE_MASK

// Low noise state macro
#define MMA8451Q_LOW_NOISE_DISABLE                          0x00
#define MMA8451Q_LOW_NOISE_ENABLE                           MMA8451Q_CTRL_REG1_LNOISE_MASK

// High pass filter state macro
#define MMA8451Q_HIGH_PASS_FILTER_DISABLE                   0x00
#define MMA8451Q_HIGH_PASS_FILTER_ENABLE                    MMA8451Q_XYZ_DATA_CFG_HPF_OUT_MASK

/* Global type define */

typedef struct mma8451q_init_struct
{
    /* Slave address is select according to SA0 pin electrical level */
    uint8_t SLAVE_ADDRESS;
    uint8_t OUTPUT_DATA_RATE;
    uint8_t FULL_SCALE_RANGE;
    uint8_t ACTIVE_POWER_SCHEME;
    uint8_t BURST_READ_MODE;
} MMA8451Q_INIT_STRUCT;

/* Function Prototype */

void * mma8451q_init
(
    MMA8451Q_INIT_STRUCT   *mma8451q_init_ptr,        /* MMA8451Q Init structure pointer */
    MQX_FILE_PTR            fd                        /* File pointer for the I2C channel */
);

bool mma8451q_deinit
(
    void       *mma8451q_handle                       /* MMA8451Q device handler */
);

bool mma8451q_write_reg
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     addr,                                 /* MMA8451Q register address */
    uint8_t    *buffer,                               /* Buffer for write function */
    uint16_t    n                                     /* Number of byte to be sent */
);

bool mma8451q_read_reg
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     addr,                                 /* MMA8451Q register address */
    uint8_t    *buffer,                               /* Buffer for read function */
    uint16_t    n                                     /* Number of byte to be read */
);

bool mma8451q_write_single_reg
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    addr,                                  /* MMA8451Q register address */
    uint8_t    data                                   /* Data to be write into MMA8451Q */
);

bool mma8451q_read_single_reg
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    addr,                                  /* MMA8451Q register address */
    uint8_t   *buffer                                 /* Buffer for storing single register value */
);

bool mma8451q_set_slave_address
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    slave_address                          /* Slave address to be set */
);

bool mma8451q_get_slave_address
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t   *buffer                                 /* Buffer to store slave address */
);

bool mma8451q_modify_bitField
(
    void       *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t     reg_address,                           /* Address of the register to be modified  */
    uint8_t     bit_field_mask,                        /* Bit field mask */
    uint8_t     bit_field_value                        /* Bit field value to be write into register */
);

bool mma8451q_get_bitField
(
    void       *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t     reg_address,                           /* Address of the register to be read  */
    uint8_t     bit_field_mask,                        /* Bit field mask */
    uint8_t    *buffer                                 /* Buffer to store register value */
);

#endif
