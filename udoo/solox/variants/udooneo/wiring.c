/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "hwtimer_mqx.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32_t millis( void )
{
	TIME_STRUCT time;

    _time_get_elapsed(&time);
   	return ((uint64_t)time.SECONDS * 1000 + time.MILLISECONDS);
}

uint32_t micros( void )
{
#ifdef	MICRO_SEC_BY_HWTIMER1
	_sched_yield();
	return (mqx_hwtimer_get_us());
#else
	return (_time_get_microseconds());
#endif
}

#ifdef	MICRO_SEC_BY_HWTIMER1
void delayMicroseconds(uint32_t usec){

	uint32_t start_us, end_us, elapsed_us;

	elapsed_us = 0;
	start_us = micros();

	while (elapsed_us < usec)
	{
		end_us = micros();
		if (end_us > start_us)
			elapsed_us += (end_us - start_us);
		start_us = end_us;
	}
}
#else
void delayMicroseconds(uint32_t usec){

	uint32_t start_us, end_us, elapsed_us;

	start_us = _time_get_microseconds();
	elapsed_us = 0;
	while (elapsed_us < usec)
	{
		end_us = _time_get_microseconds();
		if (end_us > start_us)
			elapsed_us += (end_us - start_us);
		start_us = end_us;
	}
}
#endif


// -----------------------------------------------------------------------
// delay_finer function blocks all other tasks except exit_task
// -----------------------------------------------------------------------
void delay_finer( uint32_t dwMs  )
{
	if (dwMs == 0)
        return;
    uint32_t start = millis();
    do {} while (millis() - start < dwMs);
}

#ifdef	MICRO_SEC_BY_HWTIMER1
// -----------------------------------------------------------------------
// micros_finer can be called in callback hooked from attachInterrupt
// -----------------------------------------------------------------------
uint32_t micros_finer( void )
{
	return (mqx_hwtimer_get_us());
}

// -----------------------------------------------------------------------
// delayMicroseconds_finer function blocks all other tasks except exit_task
// ------------------------------------------------------------------------
void delayMicroseconds_finer(uint32_t usec){

	uint32_t start_us, end_us, elapsed_us;

	elapsed_us = 0;
	start_us = micros_finer();

	while (elapsed_us < usec)
	{
		end_us = micros_finer();
		if (end_us > start_us)
			elapsed_us += (end_us - start_us);
		start_us = end_us;
	}
}
#endif

#ifdef __cplusplus
}
#endif
