#ifndef __mag3110_fun_h__
#define __mag3110_fun_h__
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
* FileName: mag3110_fun.h
* Version :
* Date    : Apr-21-2014
*
* Comments:
*
*   MAG3110 functional level IO interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/* Function Prototype */

bool mag3110_get_dr_status
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store Data Ready Status Register value */
);

bool mag3110_get_device_id
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store WHO_AM_I Register value */
);

bool mag3110_get_system_mode
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store SYSMOD Register value */
);

bool mag3110_set_user_offset
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    int16_t     offset_x,                             /*User Offset Correction in x axis to be set */
    int16_t     offset_y,                             /*User Offset Correction in y axis to be set */
    int16_t     offset_z                              /*User Offset Correction in z axis to be set */
);

bool mag3110_get_user_offset
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    int16_t    *offset_x,                             /* User Offset Correction in x axis from OFF_X reg */
    int16_t    *offset_y,                             /* User Offset Correction in y axis from OFF_Y reg */
    int16_t    *offset_z                              /* User Offset Correction in z axis from OFF_Z reg */
);

bool mag3110_get_temperature
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    int8_t     *buffer                                /* Buffer to store die temperature value */
);

bool mag3110_get_mag_data
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    int16_t    *data_x,                               /* Magnetic field strength in x axis */
    int16_t    *data_y,                               /* Magnetic field strength in y axis */
    int16_t    *data_z                                /* Magnetic field strength in z axis */
);

bool mag3110_set_adc_sample_rate
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     adc_sample_rate                       /* ADC rate value to be set */
);

bool mag3110_get_adc_sample_rate
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store ADC rate */
);

bool mag3110_set_over_sample_ratio
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     over_sample_ratio                     /* Over Sample Ratio value to be set */
);

bool mag3110_get_over_sample_ratio
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store Over Sample Ratio */
);

bool mag3110_set_burst_read_mode
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     read_mode                             /* Burst read mode to be set */
);

bool mag3110_get_burst_read_mode
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store Burst read mode */
);

bool mag3110_set_operating_mode
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     operating_mode                        /* Operating mode to be set */
);

bool mag3110_get_operating_mode
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store current Operating mode */
);

bool mag3110_set_auto_mrst
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     auto_reset                            /* Automatic Magnetic Sensor Reset configuration to be set */
);

bool mag3110_set_output_correction
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t     output_correction                     /* Data output correction configuration */
);

bool mag3110_get_output_correction
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store current data output correction configuration */
);

bool mag3110_trigger_measurement
(
    void       *mag3110_handle                        /* MAG3110 device handler */
);

bool mag3110_reset_mag_sensor
(
    void       *mag3110_handle                        /* MAG3110 device handler */
);

bool mag3110_get_reset_status
(
    void       *mag3110_handle,                       /* MAG3110 device handler */
    uint8_t    *buffer                                /* Buffer to store current sensor reset status */
);

#endif
