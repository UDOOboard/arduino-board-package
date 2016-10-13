/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2013 by Paul Stoffregen <paul@pjrc.com>

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

#ifndef _WIRING_
#define _WIRING_

#ifdef __cplusplus
extern "C" {
#endif

#include <mqx.h>
//#include <bsp.h>

extern void initVariant( void ) ;
extern void init( void ) ;

// return millisec since udoo-neo begin to run the program
extern uint32_t millis( void ) ;

// return microsec
// This number will overflow every 70 minutes
extern uint32_t micros( void ) ;

// delay msec, this function blocks other tasks
extern void delay_finer( uint32_t dwMs ) ;

// delay msec, this function not blocks other tasks
#define delay(ms) _time_delay(ms)

// delayMicroseconds, this function not blocks other tasks
void delayMicroseconds(uint32_t usec);

// delayMicroseconds_finer,
// this function blocks other tasks
void delayMicroseconds_finer(uint32_t usec);

// return microsec,
// this function can be called in callback hooked from attachInterrupt
extern uint32_t micros_finer( void ) ;

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ */
// delay_finer function blocks all other tasks except exit_task
