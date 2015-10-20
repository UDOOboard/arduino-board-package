#ifndef __mma8451q_reg_h__
#define __mma8451q_reg_h__
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
* FileName: mma8451q_reg.h
* Version :
* Date    : May-5-2014
*
* Comments:
*
*   mma8451q register definition and bit field masks
*
*END************************************************************************/

/* I2C Slave Address define */
#define MMA8451Q_ADDRESS_SA0_LOW     0x1C
#define MMA8451Q_ADDRESS_SA0_HIGH    0x1D
#define MMA8451Q_DEFAULT_ADDRESS     MMA8451Q_ADDRESS_SA0_LOW

/* MMA8451Q device ID number */
#define MMA8451Q_DEVICE_ID           0x1A

/* Registers address definition */
#define MMA8451Q_STATUS              0x00
#define MMA8451Q_F_STATUS            0x00
#define MMA8451Q_OUT_X_MSB           0x01
#define MMA8451Q_OUT_X_LSB           0x02
#define MMA8451Q_OUT_Y_MSB           0x03
#define MMA8451Q_OUT_Y_LSB           0x04
#define MMA8451Q_OUT_Z_MSB           0x05
#define MMA8451Q_OUT_Z_LSB           0x06
#define MMA8451Q_F_SETUP             0x09
#define MMA8451Q_TRIG_CFG            0x0A
#define MMA8451Q_SYSMOD              0x0B
#define MMA8451Q_INT_SOURCE          0x0C
#define MMA8451Q_WHO_AM_I            0x0D
#define MMA8451Q_XYZ_DATA_CFG        0x0E
#define MMA8451Q_HP_FILTER_CUTOFF    0x0F
#define MMA8451Q_PL_STATUS           0x10
#define MMA8451Q_PL_CFG              0x11
#define MMA8451Q_PL_COUNT            0x12
#define MMA8451Q_PL_BF_ZCOMP         0x13
#define MMA8451Q_P_L_THS_REG         0x14
#define MMA8451Q_FF_MT_CFG           0x15
#define MMA8451Q_FF_MT_SRC           0x16
#define MMA8451Q_FF_MT_THS           0x17
#define MMA8451Q_FF_MT_COUNT         0x18
#define MMA8451Q_TRANSIENT_CFG       0x1D
#define MMA8451Q_TRANSIENT_SCR       0x1E
#define MMA8451Q_TRANSIENT_THS       0x1F
#define MMA8451Q_TRANSIENT_COUNT     0x20
#define MMA8451Q_PULSE_CFG           0x21
#define MMA8451Q_PULSE_SRC           0x22
#define MMA8451Q_PULSE_THSX          0x23
#define MMA8451Q_PULSE_THSY          0x24
#define MMA8451Q_PULSE_THSZ          0x25
#define MMA8451Q_PULSE_TMLT          0x26
#define MMA8451Q_PULSE_LTCY          0x27
#define MMA8451Q_PULSE_WIND          0x28
#define MMA8451Q_ASLP_COUNT          0x29
#define MMA8451Q_CTRL_REG1           0x2A
#define MMA8451Q_CTRL_REG2           0x2B
#define MMA8451Q_CTRL_REG3           0x2C
#define MMA8451Q_CTRL_REG4           0x2D
#define MMA8451Q_CTRL_REG5           0x2E
#define MMA8451Q_OFF_X               0x2F
#define MMA8451Q_OFF_Y               0x30
#define MMA8451Q_OFF_Z               0x31

/* MMA8451Q Register Masks */

/* Data Status Register Bit Fields */
#define MMA8451Q_STATUS_ZYXOW_MASK                  0x80
#define MMA8451Q_STATUS_ZOW_MASK                    0x40
#define MMA8451Q_STATUS_YOW_MASK                    0x20
#define MMA8451Q_STATUS_XOW_MASK                    0x10
#define MMA8451Q_STATUS_ZYXDR_MASK                  0x08
#define MMA8451Q_STATUS_ZDR_MASK                    0x04
#define MMA8451Q_STATUS_YDR_MASK                    0x02
#define MMA8451Q_STATUS_XDR_MASK                    0x01

/* Output Data Register Bit Fields*/
#define MMA8451Q_OUT_DATA_SHIFT                     0x02

/* FIFO STATUS Register Bit Fields */
#define MMA8451Q_F_STATUS_OVF_MASK                  0x80
#define MMA8451Q_F_STATUS_WMRK_FLAG_MASK            0x40
#define MMA8451Q_F_STATUS_CNT_MASK                  0x3F

/* FIFO Setup Register Bit Fields */
#define MMA8451Q_F_SETUP_MODE_MASK                  0xC0
#define MMA8451Q_F_SETUP_WMRK_MASK                  0x3F

/* Trigger Configuration Register Bit Fields */
#define MMA9451Q_TRIG_CFG_MASK                      0x3C
#define MMA8451Q_TRIG_CFG_TRANS_MASK                0x20
#define MMA8451Q_TRIG_CFG_LNDPRT_MASK               0x10
#define MMA8451Q_TRIG_CFG_PULSE_MASK                0x08
#define MMA8451Q_TRIG_CFG_FF_MT_MASK                0x04

/* System Mode Register Bit Fields */
#define MMA8451Q_SYSMOD_FGERR_MASK                  0x80
#define MMA8451Q_SYSMOD_FGT_MASK                    0x7C
#define MMA8451Q_SYSMOD_FGT_SHIFT                   0x02
#define MMA8451Q_SYSMOD_SYSMOD_MASK                 0x03

/* System Interrupt Status Register Bit Fields */
#define MMA8451Q_INT_SOURCE_MASK                    0xFD
#define MMA8451Q_INT_SOURCE_ASLP_MASK               0x80
#define MMA8451Q_INT_SOURCE_FIFO_MASK               0x40
#define MMA8451Q_INT_SOURCE_TRANS_MASK              0x20
#define MMA8451Q_INT_SOURCE_LNDPRT_MASK             0x10
#define MMA8451Q_INT_SOURCE_PULSE_MASK              0x08
#define MMA8451Q_INT_SOURCE_FF_MT_MASK              0x04
#define MMA8451Q_INT_SOURCE_DRDY_MASK               0x01

/* XYZ Data Configuration Bit Fields */
#define MMA8451Q_XYZ_DATA_CFG_HPF_OUT_MASK          0x10
#define MMA8451Q_XYZ_DATA_CFG_FS_MASK               0x03

/* High-Pass Filter Register Bit Fields */
#define MMA8451Q_HP_FILTER_CUTOFF_P_HPF_BYP_MASK    0x20
#define MMA8451Q_HP_FILTER_CUTOFF_P_LPF_EN_MASK     0x10
#define MMA8451Q_HP_FILTER_CUTOFF_SEL_MASK          0x03

/* Portrait/Landscape Status Register Bit Fields */
#define MMA8451Q_PL_STATUS_NEWLP_MASK               0x80
#define MMA8451Q_PL_STATUS_LO_MASK                  0x40
#define MMA8451Q_PL_STATUS_LAPO_MASK                0x06
#define MMA8451Q_PL_STATUS_BAFRO_MASK               0x01

/* Portrait/Landscape Configuration Register Bit Fields */
#define MMA8451Q_PL_CFG_DBCNTM_MASK                 0x80
#define MMA8451Q_PL_CFG_PL_EN_MASK                  0x40

/* Back/Front and Z Compensation Register Bit Fields */
#define MMA8451Q_PL_BF_ZCOMP_BKFR_MASK              0xC0
#define MMA8451Q_PL_BF_ZCOMP_ZLOCK_MASK             0x07

/* Portrait/Landscape Threshold and Hysteresis Register Bit Fields  */
#define MMA8451Q_P_L_THS_REG_THS_MASK               0xF8
#define MMA8451Q_P_L_THS_REG_HYS_MASK               0x07
#define MMA8451Q_P_L_THS_REG_THS_SHIFT              0X03

/* Freefall/Motion Configuration Register Bit Fields */
#define MMA8451Q_FF_MT_CFG_ELE_MASK                 0x80
#define MMA8451Q_FF_MT_CFG_OAE_MASK                 0x40
#define MMA8451Q_FF_MT_CFG_ZEFE_MASK                0x20
#define MMA8451Q_FF_MT_CFG_YEFE_MASK                0x10
#define MMA8451Q_FF_MT_CFG_XEFE_MASK                0x08

/* Freefall/Motion Source Register Bit Fields */
#define MMA8451Q_FF_MT_SRC_EA_MASK                  0x80
#define MMA8451Q_FF_MT_SRC_ZHE_MASK                 0x20
#define MMA8451Q_FF_MT_SRC_ZHP_MASK                 0x10
#define MMA8451Q_FF_MT_SRC_YHE_MASK                 0x08
#define MMA8451Q_FF_MT_SRC_YHP_MASK                 0x04
#define MMA8451Q_FF_MT_SRC_XHE_MASK                 0x02
#define MMA8451Q_FF_MT_SRC_XHP_MASK                 0x01

/* Freefall and Motion Threshold Register Bit Fields */
#define MMA8451Q_FF_MT_THS_DBCNTM_MASK              0x80
#define MMA8451Q_FF_MT_THS_THS_MASK                 0x7F

/* Transient_CFG Register Bit Fields */
#define MMA8451Q_TRANSIENT_CFG_ELE_MASK             0x10
#define MMA8451Q_TRANSIENT_CFG_ZTEFE_MASK           0x08
#define MMA8451Q_TRANSIENT_CFG_YTEFE_MASK           0x04
#define MMA8451Q_TRANSIENT_CFG_XTEFE_MASK           0x02
#define MMA8451Q_TRANSIENT_CFG_HPF_BYP_MASK         0x01

/* TRANSIENT_SRC Register Bit Fields */
#define MMA8451Q_TRANSIENT_SRC_EA_MASK              0x40
#define MMA8451Q_TRANSIENT_SRC_Z_MASK               0x20
#define MMA8451Q_TRANSIENT_SRC_Z_POL_MASK           0x10
#define MMA8451Q_TRANSIENT_SRC_Y_MASK               0x08
#define MMA8451Q_TRANSIENT_SRC_Y_POL_MASK           0x04
#define MMA8451Q_TRANSIENT_SRC_X_MASK               0x02
#define MMA8451Q_TRANSIENT_SRC_X_POL_MASK           0x01

/* TRANSIENT_THS Register Bit Fields */
#define MMA8451Q_TRANSIENT_THS_DBCNTM_MASK          0x80
#define MMA8451Q_TRANSIENT_THS_THS_MASK             0x7F

/* Pulse Configuration Register Bit Fields */
#define MMA8451Q_PULSE_CFG_DPA_MASK                 0x80
#define MMA8451Q_PULSE_CFG_ELE_MASK                 0x40
#define MMA8451Q_PULSE_CFG_ZDPEFE_MASK              0x20
#define MMA8451Q_PULSE_CFG_ZSPEFE_MASK              0x10
#define MMA8451Q_PULSE_CFG_YDPEFE_MASK              0x08
#define MMA8451Q_PULSE_CFG_YSPEFE_MASK              0x04
#define MMA8451Q_PULSE_CFG_XDPEFE_MASK              0x08
#define MMA8451Q_PULSE_CFG_XSPEFE_MASK              0x04

/* Pulse Source Register Bit Fields */
#define MMA8451Q_PULSE_SRC_EA_MASK                  0x80
#define MMA8451Q_PULSE_SRC_AXZ_MASK                 0x40
#define MMA8451Q_PULSE_SRC_AXY_MASK                 0x20
#define MMA8451Q_PULSE_SRC_AXX_MASK                 0x10
#define MMA8451Q_PULSE_SRC_DPE_MASK                 0x08
#define MMA8451Q_PULSE_SRC_POL_Z_MASK               0x04
#define MMA8451Q_PULSE_SRC_POL_Y_MASK               0x02
#define MMA8451Q_PULSE_SRC_POL_X_MASK               0x01

/* PULSE_THS Register Bit Fields */
#define MMA8451Q_PULSE_THS_MASK                     0x7F

/* CTRL_REG1 System Control 1 Register Bit Fields */
#define MMA8451Q_CTRL_REG1_ASLP_RATE_MASK           0xC0
#define MMA8451Q_CTRL_REG1_DR_MASK                  0x38
#define MMA8451Q_CTRL_REG1_LNOISE_MASK              0x04
#define MMA8451Q_CTRL_REG1_F_READ_MASK              0x02
#define MMA8451Q_CTRL_REG1_ACTIVE_MASK              0x01

/* CTRL_REG2 System Control 2 Register Bit Fields */
#define MMA8451Q_CTRL_REG2_ST_MASK                  0x80
#define MMA8451Q_CTRL_REG2_RST_MASK                 0x40
#define MMA8451Q_CTRL_REG2_SMODS_MASK               0x18
#define MMA8451Q_CTRL_REG2_SLPE_MASK                0x04
#define MMA8451Q_CTRL_REG2_MODS_MASK                0x03

/* CTRL_REG3 Interrupt Control Register Bit Fields */
#define MMA8451Q_CTRL_REG3_FIFO_GATE_MASK           0x80
#define MMA8451Q_CTRL_REG3_WAKE_MASK                0x78
#define MMA8451Q_CTRL_REG3_WAKE_TRANS_MASK          0x40
#define MMA8451Q_CTRL_REG3_WAKE_LNDPRT_MASK         0x20
#define MMA8451Q_CTRL_REG3_WAKE_PULSE_MASK          0x10
#define MMA8451Q_CTRL_REG3_WAKE_FF_MT_MASK          0x08
#define MMA8451Q_CTRL_REG3_IPOL_MASK                0x02
#define MMA8451Q_CTRL_REG3_PP_OD_MASK               0x01

/* CTRL_REG4 Register Bit Fields */
#define MMA8451Q_CTRL_REG4_INT_EN_MASK              0xFD
#define MMA8451Q_CTRL_REG4_INT_EN_ASLP_MASK         0x80
#define MMA8451Q_CTRL_REG4_INT_EN_FIFO_MASK         0x40
#define MMA8451Q_CTRL_REG4_INT_EN_TRANS_MASK        0x20
#define MMA8451Q_CTRL_REG4_INT_EN_LNDPR_MASK        0x10
#define MMA8451Q_CTRL_REG4_INT_EN_PULSE_MASK        0x08
#define MMA8451Q_CTRL_REG4_INT_EN_FF_MT_MASK        0x04
#define MMA8451Q_CTRL_REG4_INT_EN_DRDY_MASK         0x01

/* CTRL_REG5 Interrupt Configuration Register */
#define MMA8451Q_CTRL_REG5_INT_CFG_ASLP_MASK        0x80
#define MMA8451Q_CTRL_REG5_INT_CFG_FIFO_MASK        0x40
#define MMA8451Q_CTRL_REG5_INT_CFG_TRANS_MASK       0x20
#define MMA8451Q_CTRL_REG5_INT_CFG_LNDPRT_MASK      0x10
#define MMA8451Q_CTRL_REG5_INT_CFG_PULSE_MASK       0x08
#define MMA8451Q_CTRL_REG5_INT_CFG_FF_MT_MASK       0x04
#define MMA8451Q_CTRL_REG5_INT_CFG_DRDY_MASK        0x01

#endif
