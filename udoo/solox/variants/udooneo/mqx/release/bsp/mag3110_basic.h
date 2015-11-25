#ifndef __mag3110_basic_h__
#define __mag3110_basic_h__
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
* FileName: mag3110_basic.h
* Version :
* Date    : Apr-21-2014
*
* Comments:
*
*   MAG3110 basic IO interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

#include "mqx.h"

#include "mag3110_reg.h"

/* Useful macros */

// Data ready status macro
#define MAG3110_DATA_READY_ZYXOW          MAG3110_DR_STATUS_ZYXOW_MASK
#define MAG3110_DATA_READY_ZOW            MAG3110_DR_STATUS_ZOW_MASK
#define MAG3110_DATA_READY_YOW            MAG3110_DR_STATUS_YOW_MASK
#define MAG3110_DATA_READY_XOW            MAG3110_DR_STATUS_XOW_MASK
#define MAG3110_DATA_READY_ZYXDR          MAG3110_DR_STATUS_ZYXDR_MASK
#define MAG3110_DATA_READY_ZDR            MAG3110_DR_STATUS_ZDR_MASK
#define MAG3110_DATA_READY_YDR            MAG3110_DR_STATUS_YDR_MASK
#define MAG3110_DATA_READY_XDR            MAG3110_DR_STATUS_XDR_MASK

// System mode macro
#define MAG3110_SYSMOD_STANDBY            0x00
#define MAG3110_SYSMOD_ACTIVE_RAW         0x01
#define MAG3110_SYSMOD_ACTIVE_NORMAL      0x02

// ADC sample rate macro
// There are many combination of ADC sample rate and over sample ratio.
// Each combination corresponds to different consumption Level.
// Refer to MAG3110 datasheet page 20 for detail.
#define MAG3110_ADC_SAMPLE_RATE_80HZ      0x80
#define MAG3110_ADC_SAMPLE_RATE_160HZ     0x60
#define MAG3110_ADC_SAMPLE_RATE_320HZ     0x40
#define MAG3110_ADC_SAMPLE_RATE_640HZ     0x20
#define MAG3110_ADC_SAMPLE_RATE_1280HZ    0x00

// Over sample ratio macro
#define MAG3110_OVER_SAMPLE_RATIO_16      0x00
#define MAG3110_OVER_SAMPLE_RATIO_32      0x08
#define MAG3110_OVER_SAMPLE_RATIO_64      0x10
#define MAG3110_OVER_SAMPLE_RATIO_128     0x18

// Burst read mode macro
#define MAG3110_BURST_READ_MODE_NORMAL    0x00
#define MAG3110_BURST_READ_MODE_FAST      MAG3110_CTRL_REG1_FR_MASK

// Operating mode macro
#define MAG3110_OPERATING_MODE_STANDBY    0x00
#define MAG3110_OPERATING_MODE_ACTIVE     MAG3110_CTRL_REG1_AC_MASK

// Automatic magnetic sensor reset macro
#define MAG3110_AUTO_MRST_DISABLE         0x00
#define MAG3110_AUTO_MRST_ENABLE          MAG3110_CTRL_REG2_AUTO_MRST_EN_MASK

// Data correction
#define MAG3110_OUTPUT_CORRECT_DISABLE    MAG3110_CTRL_REG2_RAW_MASK
#define MAG3110_OUTPUT_CORRECT_ENABLE     0x00

/* Global type define */

typedef struct mag3110_init_struct
{
    uint8_t SLAVE_ADDRESS;
    uint8_t ADC_SAMPLE_RATE;
    uint8_t OVER_SAMPLE_RATIO;
    uint8_t BURST_READ_MODE;
    uint8_t AUTO_MRST_MODE;
    uint8_t DATA_CORRECTION_MODE;
}MAG3110_INIT_STRUCT;

/* Function Prototype */

void * mag3110_init
(
    MAG3110_INIT_STRUCT   *mag3110_init_ptr,          /* MAG3110 Init structure pointer */
    MQX_FILE_PTR           fd                         /* File pointer for the I2C channel */
);

bool mag3110_deinit
(
    void    *mag3110_handle                           /* MAG3110 device handler */
);

bool mag3110_write_reg
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     addr,                                 /* MAG3110 register address */
    uint8_t    *buffer,                               /* Buffer for write function */
    uint16_t    n                                     /* Number of byte to be sent */

);

bool mag3110_read_reg
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     addr,                                 /* MAG3110 register address */
    uint8_t    *buffer,                               /* Buffer for read function */
    uint16_t    n                                     /* Number of byte to be read */
);

bool mag3110_write_single_reg
(
    void      *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    addr,                                 /* MAG3110 register address */
    uint8_t    data                                  /* Data to be write into MAG3110 */
);

bool mag3110_read_single_reg
(
    void      *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    addr,                                 /* MAG3110 register address */
    uint8_t   *buffer                                /* Buffer for storing single register value */
);

bool mag3110_set_slave_address
(
    void      *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    slave_address                         /* Slave address to be set */
);

bool mag3110_get_slave_address
(
    void      *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t   *buffer                                /* Buffer to store slave address */
);

#endif
