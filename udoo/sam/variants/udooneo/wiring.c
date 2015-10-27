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

/*
// -------------------------------------------
// get the absolute time in milliseconds
// if SECONDS > 4294967 then reset absolute time for avoid uint32_t overflow
// the other option is to return uint64_t value
// Not work: after reset, read always 0
// -------------------------------------------
uint32_t millis( void )
{
	TIME_STRUCT time;

    _time_get_elapsed(&time);
	if (time.SECONDS > 4294967ul) {
		time.SECONDS = 0;
		time.MILLISECONDS = 0;
		_time_set(&time);
		return (0);
	}
   	return (time.SECONDS * 1000 + time.MILLISECONDS);
}
*/

uint64_t millis( void )
{
	TIME_STRUCT time;

    _time_get_elapsed(&time);
   	return ((uint64_t)time.SECONDS * 1000 + time.MILLISECONDS);
}

uint32_t micros( void )
{
#ifdef	MICRO_SEC_BY_HWTIMER1
	return (mqx_hwtimer_get_us());
#else
	return (_time_get_microseconds());
#endif
}

// This delay function blocks all other tasks !!!
void delay_finer( uint32_t dwMs  )
{
	if (dwMs == 0)
        return;
    uint32_t start = millis();
    do {} while (millis() - start < dwMs);
}

/* not work fine, reset time is variable ((1122, 3777), not 5000
void delayMicroseconds(uint32_t usec){

	uint32_t start_us, end_us, elapsed_us;
	uint32_t usecTimeResolution;

	start_us = _time_get_microseconds();
	usecTimeResolution = _time_get_resolution() * 1000;
	elapsed_us = 0;
	do {
		end_us = _time_get_microseconds();
		if (end_us >= start_us)
			elapsed_us += (end_us - start_us);
		else
			elapsed_us += (usecTimeResolution - start_us + end_us);
		start_us = end_us;
	}while (elapsed_us < usec);
}
*/

#ifdef	MICRO_SEC_BY_HWTIMER1
void delayMicroseconds(uint32_t usec){

	uint32_t start_us, end_us, elapsed_us;

	start_us = micros();
	elapsed_us = 0;
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

#ifdef __cplusplus
}
#endif
