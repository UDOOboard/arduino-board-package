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

/**
 *
 */
extern void initVariant( void ) ;
extern void init( void ) ;

// return millisec since the udoo-neo board began runnig the program
extern uint64_t millis( void ) ;

// return mocrosec
// This number will overflow every ????
extern uint32_t micros( void ) ;

// delay msec, this function blocks other tasks
extern void delay_finer( uint32_t dwMs ) ;

// delay msec, this function not blocks other tasks
#define delay(ms) _time_delay(ms)

// delayMicroseconds, this function blocks other tasks
void delayMicroseconds(uint32_t usec);

#ifdef __cplusplus
}
#endif

#endif /* _WIRING_ */
