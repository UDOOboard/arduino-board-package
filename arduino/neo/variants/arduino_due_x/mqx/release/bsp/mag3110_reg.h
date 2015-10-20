#ifndef __mag3110_reg_h__
#define __mag3110_reg_h__
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
* FileName: mag3110_reg.h
* Version :
* Date    : Apr-21-2014
*
* Comments:
*
*   mag3110 register definition and bit field masks
*
*END************************************************************************/

/* I2C Slave Address define */
#define MAG3110FCR1_ADDRESS        0x0E
#define FXMS3110CDR1_ADDRESS       0x0F
#define MAG3110_DEFAULT_ADDRESS    MAG3110FCR1_ADDRESS

/* MAG3110 device ID number */
#define MAG3110_DEVICE_ID          0xC4

/* Registers address definition */
#define MAG3110_DR_STATUS          0x00
#define MAG3110_OUT_X_MSB          0x01
#define MAG3110_OUT_X_LSB          0x02
#define MAG3110_OUT_Y_MSB          0x03
#define MAG3110_OUT_Y_LSB          0x04
#define MAG3110_OUT_Z_MSB          0x05
#define MAG3110_OUT_Z_LSB          0x06
#define MAG3110_WHO_AM_I           0x07
#define MAG3110_SYSMOD             0x08
#define MAG3110_OFF_X_MSB          0x09
#define MAG3110_OFF_X_LSB          0x0A
#define MAG3110_OFF_Y_MSB          0x0B
#define MAG3110_OFF_Y_LSB          0x0C
#define MAG3110_OFF_Z_MSB          0x0D
#define MAG3110_OFF_Z_LSB          0x0E
#define MAG3110_DIE_TEMP           0x0F
#define MAG3110_CTRL_REG1          0x10
#define MAG3110_CTRL_REG2          0x11

/* MAG3110 Register Masks */

/* DR_STATUS Bit Fields */
#define MAG3110_DR_STATUS_ZYXOW_MASK           0x80
#define MAG3110_DR_STATUS_ZOW_MASK             0x40
#define MAG3110_DR_STATUS_YOW_MASK             0x20
#define MAG3110_DR_STATUS_XOW_MASK             0x10
#define MAG3110_DR_STATUS_ZYXDR_MASK           0x08
#define MAG3110_DR_STATUS_ZDR_MASK             0x04
#define MAG3110_DR_STATUS_YDR_MASK             0x02
#define MAG3110_DR_STATUS_XDR_MASK             0x01

/* SYSMOD Bit Fields */
#define MAG3110_SYSMOD_MASK                    0x03

/* User Offset Correction Fields */
#define MAG3110_OFFSET_SHIFT                   0x01

/* CTRL_REG1 Bit Fields */
#define MAG3110_CTRL_REG1_DR_MASK              0xE0
#define MAG3110_CTRL_REG1_OS_MASK              0x18
#define MAG3110_CTRL_REG1_FR_MASK              0x04
#define MAG3110_CTRL_REG1_TM_MASK              0x02
#define MAG3110_CTRL_REG1_AC_MASK              0x01

/* CTRL_REG2 Bit Fields */
#define MAG3110_CTRL_REG2_AUTO_MRST_EN_MASK    0x80
#define MAG3110_CTRL_REG2_RAW_MASK             0x20
#define MAG3110_CTRL_REG2_MAG_RST_MASK         0x10

#endif
