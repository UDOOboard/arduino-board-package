/*
  Copyright (c) 2015 SECO s.r.l  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

*/

// this file is a wrapper for call mqx api without conflict with stdio.h, stdlib.h
// fio.h redefine write, read etc..

#include <mqx.h>
#include <bsp.h>
#include "log_mqx.h"
#include "pwm_ifc.h"
#include "servo_mqx.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


/*	the parameters setting below for:
 *
 *	50Hz pwm frequency
 *  60000 ticks pwm resolution
 *
 *	for different setting read IMX6SXRM.pdf 49.7.5
 */

void mqx_servo_attach (uint16_t pwmChn, uint16_t defPulseWidth)
{

	if (!PwmIsEnabled(pwmChn)) {
		// PWM Startup code
    	_bsp_pwm_io_init(pwmChn, 0xff);
		pwm_disable(pwmChn);
		pwm_set_clock(pwmChn, kPwmClockSourceIpg);
    	pwm_set_fwm(pwmChn, DEF_SERVO_FWM);
    	pwm_set_prescaler(pwmChn, DEF_SERVO_PRESCALER);
    	pwm_set_poutc(pwmChn, DEF_SERVO_ACT_POL);
    	pwm_set_period(pwmChn, DEF_SERVO_TICKS_PERIOD);
    	pwm_set_resolution(pwmChn, DEF_SERVO_TICKS_PERIOD);
    	pwm_set_repeat(pwmChn, DEF_SERVO_REPEAT);
		pwm_enable(pwmChn);
	}
   	pwm_set_sample(pwmChn, defPulseWidth);
}

void mqx_servo_detach(uint16_t pwmChn)
{
	pwm_disable(pwmChn);
	_bsp_pwm_io_init(pwmChn, 0x00);
}
