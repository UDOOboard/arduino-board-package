/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*
*   This file includes all include files specific to this target system.
*
*
*END************************************************************************/

#ifndef _bsp_h_
#define _bsp_h_ 1

#include <bsp_rev.h>
#include <psp.h>
#include <imx6sx_sdb_m4.h>

#include <nvic.h>

/* Clock manager */
#include <bsp_cm.h>
#include <cm_imx6sx.h>
#include <cm.h>

#include <fio.h>
#include <io.h>

#include <serial.h>
#include <serl_imx_uart.h>

#include <lwadc_imxadc.h>

#include <i2c.h>
#include <i2c_imx.h>


#include <hwtimer.h>
#include <hwtimer_epit.h>
#include <hwtimer_systick.h>

#include <lwgpio_igpio.h>
#include <lwgpio.h>

/* Low power manager*/
#include <init_lpm.h>
#include <lpm_imx6sx.h>
#include <lpm.h>

#include <spi_bsp_mqx.h>
#include <spi_ecspi.h>
#include <spi_slave_ecspi.h>

#include <clk_api.h>
#include <mu.h>

#include <lpm_mcore.h>

#ifdef __cplusplus
extern "C" {
#endif

_mqx_int _bsp_gpio_io_init( void );
_mqx_int _bsp_i2c_io_init( _mqx_uint dev_num, _mqx_uint flags );
_mqx_int _bsp_serial_io_init( _mqx_uint dev_num, _mqx_uint flags);

_mqx_int _bsp_adc_io_init( _mqx_uint adc_num );
_mqx_int _bsp_adc_channel_io_init( _mqx_uint channel );
_mqx_int _bsp_flexcan_io_init(_mqx_uint dev_num);
_mqx_int _bsp_mcan_io_init(_mqx_uint dev_num);
_mqx_int _bsp_ecspi_io_init( _mqx_uint dev_num, _mqx_uint flags);
_mqx_int _bsp_ecspi_slave_io_init( _mqx_uint dev_num);
_mqx_int _bsp_pwm_io_init( _mqx_uint dev_num, _mqx_uint flags);

extern const LPM_CPU_OPERATION_MODE LPM_CPU_OPERATION_MODES[];

static inline uint32_t _bsp_int_init(_mqx_uint num, _mqx_uint prior, _mqx_uint subprior, bool enable) {
    uint32_t res;

    if (MQX_OK == (res = _nvic_int_init(num, prior, enable))) {
    }

    return res;
}

#define _bsp_int_enable(num)                            _nvic_int_enable(num)
#define _bsp_int_disable(num)                           _nvic_int_disable(num)

#ifdef __cplusplus
}
#endif

#endif  /* _bsp_h_ */
