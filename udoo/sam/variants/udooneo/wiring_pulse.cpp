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

#include <mqx.h>
#include <bsp.h>

#include "Arduino.h"
#include "wiring_private.h"
#include "log_mqx.h"

/*
  Copyright (c) 2011-2012 Arduino.  All right reserved.

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

extern LWGPIO_STRUCT ardDio[ARD_NMAX_DIO];

/* Measures the length (in microseconds) of a pulse on the pin; state is HIGH
 * or LOW, the type of pulse to measure.  Works on pulses from 2-3 microseconds
 * to 3 minutes in length, but must be called at least a few dozen microseconds
 * before the start of the pulse. */
extern uint32_t pulseIn( uint32_t pin, uint32_t state, uint32_t timeout )
{
	if (pin >= ARD_NMAX_DIO) return 0;
	
	// convert the timeout from microseconds to a number of times through
	// the initial loop; it takes 22 clock cycles per iteration.
	uint32_t sMicros;
	uint32_t eMicros;
	uint32_t dMicros = 0;
	// wait for any previous pulse to end
	sMicros = micros();
	while (digitalRead(pin) == state) {
		eMicros = micros();
		if (eMicros > sMicros) {
			dMicros += (eMicros - sMicros);
			sMicros = eMicros;
			if (dMicros > timeout)
				return 0;
		}
	}
	
	// wait for the pulse to start
	while (digitalRead(pin) != state) {
		eMicros = micros();
		if (eMicros > sMicros) {
			dMicros += (eMicros - sMicros);
			sMicros = eMicros;
			if (dMicros > timeout)
				return 0;
		}
	}
	
	// wait for the pulse to stop
	sMicros = micros();
	dMicros = 0;
	while (digitalRead(pin) == state) {
		eMicros = micros();
		if (eMicros > sMicros) {
			dMicros += (eMicros - sMicros);
			sMicros = eMicros;
			if (dMicros > timeout)
				return 0;
		}
	}

	eMicros = micros();
	if (eMicros > sMicros) {
		dMicros += (eMicros - sMicros);
	}
	return (dMicros);
}
