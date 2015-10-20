#ifndef __mma8451q_generic_h__
#define __mma8451q_generic_h__
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
* FileName: mma8451q_generic.h
* Version :
* Date    : May-16-2014
*
* Comments:
*
*   MMA8451Q functional level generic IO interface
*
*END************************************************************************/

#include <stdint.h>
#include <stdbool.h>

/* Function Prototype */

bool mma8451q_get_dr_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store Data Ready Status Register value */
);

bool mma8451q_get_device_id
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store WHO_AM_I Register value */
);

bool mma8451q_get_system_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store SYSMOD value */
);

bool mma8451q_set_output_data_rate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     output_rate                           /* Output data rate to be set  */
);

bool mma8451q_get_output_data_rate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store output data rate */
);

bool mma8451q_set_power_scheme
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     power_scheme                          /* Power scheme to be set */
);

bool mma8451q_get_power_scheme
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store power scheme */
);

bool mma8451q_set_full_scale_range
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     full_scale                            /* Full scale range to be set */
);

bool mma8451q_get_full_scale_range
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store full scale range */
);

bool mma8451q_set_burst_read_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     read_mode                             /* Burst read mode to be set */
);

bool mma8451q_get_burst_read_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store burst read mode */
);

bool mma8451q_set_user_offset
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    int8_t      offset_x,                             /* User Offset Correction in x axis to be set */
    int8_t      offset_y,                             /* User Offset Correction in y axis to be set */
    int8_t      offset_z                              /* User Offset Correction in z axis to be set */
);

bool mma8451q_get_user_offset
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    int8_t     *offset_x,                             /* User Offset Correction in x axis from OFF_X reg */
    int8_t     *offset_y,                             /* User Offset Correction in y axis from OFF_X reg */
    int8_t     *offset_z                              /* User Offset Correction in z axis from OFF_X reg */
);

bool mma8451q_get_acc_data
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    int16_t    *data_x,                               /* Acceleration data in x axis */
    int16_t    *data_y,                               /* Acceleration data in y axis */
    int16_t    *data_z                                /* Acceleration data in z axis */
);

bool mma8451q_set_self_test_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     st_enabled                            /* Self test function enable state */
);

bool mma8451q_get_self_test_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store self test state */
);

bool mma8451q_reset_sensor
(
    void       *mma8451q_handle                       /* MMA8451Q device handler */
);

bool mma8451q_get_senor_reset_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store reset state */
);

bool mma8451q_set_operating_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     operating_mode                        /* Operating mode to be set */
);

bool mma8451q_get_operating_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store current operating mode */
);

bool mma8451q_set_fifo_watermark
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     watermark                             /* FIFO watermark to be set */
);

bool mma8451q_get_fifo_watermark
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store FIFO watermark */
);

bool mma8451q_set_fifo_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     fifo_mode                             /* FIFO mode to be set */
);

bool mma8451q_get_fifo_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store FIFO mode */
);

bool mma8451q_set_fifo_trigger_source
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     trigger_source                        /* FIFO trigger source to be set */
);

bool mma8451q_get_fifo_trigger_source
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store FIFO trigger source */
);

bool mma8451q_set_fifo_gate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     fifo_gate                             /* FIFO gate to be set */
);

bool mma8451q_get_fifo_gate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store FIFO gate */
);

bool mma8451q_get_fifo_status
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store FIFO status */
);

bool mma8451q_get_fifo_count
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store fifo count */
);

bool mma8451q_get_acc_from_fifo
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer,                               /* Buffer to store acc data */
    uint8_t     n                                     /* Number of fifo count to be read from FIFO */
);

bool mma8451q_set_int_polarity
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     polarity                              /* MMA8451Q interrupt polarity to be set */
);

bool mma8451q_get_int_polarity
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store interrupt polarity */
);

bool mma8451q_set_int_output_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     output_mode                           /* MMA8451Q interrupt output mode to be set */
);

bool mma8451q_get_int_output_mode
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store interrupt output mode */
);

bool mma8451q_set_int_pin_route
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     pin_route                             /* MMA8451Q interrupt pin route to be set */
);

bool mma8451q_get_int_pin_route
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store interrupt pin route */
);

bool mma8451q_set_int_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     int_enabled                           /* MMA8451Q interrupt state to be set */
);

bool mma8451q_get_int_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store interrupt state */
);

bool mma8451q_get_int_source
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store interrupt source flag */
);

bool mma8451q_set_aslp_output_data_rate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     output_rate                           /* Asleep data output rate to be set */
);

bool mma8451q_get_aslp_output_data_rate
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store asleep data output rate */
);

bool mma8451q_set_aslp_power_scheme
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     power_scheme                          /* Asleep power scheme to be set */
);

bool mma8451q_get_aslp_power_scheme
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store asleep power scheme */
);

bool mma8451q_set_wake_up_bypass
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     wake_up_bypass                        /* Wake up bypass event to be set */
);

bool mma8451q_get_wake_up_bypass
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store wake up bypass event */
);

bool mma8451q_set_aslp_count
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     aslp_count                            /* Auto sleep count to be set */
);

bool mma8451q_get_aslp_count
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store auto sleep count */
);

bool mma8451q_set_aslp_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t     aslp_enabled                          /* Auto sleep function enable config */
);

bool mma8451q_get_aslp_state
(
    void       *mma8451q_handle,                      /* MMA8451Q device handler */
    uint8_t    *buffer                                /* Buffer to store auto sleep enable state */
);

bool mma8451q_set_low_noise_state
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    lnoise_enabled                         /* Low noise enable state */
);

bool mma8451q_get_low_noise_state
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t   *buffer                                 /* Buffer to store low noise enable state */
);

bool mma8451q_set_hpf_cutoff
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    hpf_cutoff                             /* High pass filter cutoff configuration */
);

bool mma8451q_get_hpf_cutoff
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t   *buffer                                 /* Buffer to store high pass filter cutoff configuration */
);

bool mma8451q_set_hpf_state
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t    hpf_enabled                            /* High pass filter enable state */
);

bool mma8451q_get_hpf_state
(
    void      *mma8451q_handle,                       /* MMA8451Q device handler */
    uint8_t   *buffer                                 /* Buffer to store high pass filter enable state */
);

#endif
