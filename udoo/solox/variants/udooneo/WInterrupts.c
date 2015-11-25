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
#include <mqx.h>
#include <bsp.h>

#include "log_mqx.h"
#include "WInterrupts.h"

typedef void (*interruptCB)(void *);

extern LWGPIO_STRUCT ardDio[ARD_NMAX_DIO];

static interruptCB int_service_routine_ard_pin[ARD_NMAX_DIO];
static void (*callback_ard_pin[ARD_NMAX_DIO])(void);

static void int_service_routine0(void *pin) {

//    lwgpio_int_clear_flag((LWGPIO_STRUCT_PTR) pin);
    lwgpio_int_clear_flag(&ardDio[0]);
    callback_ard_pin[0]();
}

static void int_service_routine1(void *pin) {
    lwgpio_int_clear_flag(&ardDio[1]);
    callback_ard_pin[1]();
}

static void int_service_routine2(void *pin) {
    lwgpio_int_clear_flag(&ardDio[2]);
    callback_ard_pin[2]();
}
static void int_service_routine3(void *pin) {
    lwgpio_int_clear_flag(&ardDio[3]);
    callback_ard_pin[3]();
}
static void int_service_routine4(void *pin) {
    lwgpio_int_clear_flag(&ardDio[4]);
    callback_ard_pin[4]();
}
static void int_service_routine5(void *pin) {
    lwgpio_int_clear_flag(&ardDio[5]);
    callback_ard_pin[5]();
}
static void int_service_routine6(void *pin) {
    lwgpio_int_clear_flag(&ardDio[6]);
    callback_ard_pin[6]();
}
static void int_service_routine7(void *pin) {
    lwgpio_int_clear_flag(&ardDio[7]);
    callback_ard_pin[7]();
}
static void int_service_routine8(void *pin) {
    lwgpio_int_clear_flag(&ardDio[8]);
    callback_ard_pin[8]();
}
static void int_service_routine9(void *pin) {
    lwgpio_int_clear_flag(&ardDio[9]);
    callback_ard_pin[9]();
}
static void int_service_routine10(void *pin) {
    lwgpio_int_clear_flag(&ardDio[10]);
    callback_ard_pin[10]();
}
static void int_service_routine11(void *pin) {
    lwgpio_int_clear_flag(&ardDio[11]);
    callback_ard_pin[11]();
}
static void int_service_routine12(void *pin) {
    lwgpio_int_clear_flag(&ardDio[12]);
    callback_ard_pin[12]();
}
static void int_service_routine13(void *pin) {
    lwgpio_int_clear_flag(&ardDio[13]);
    callback_ard_pin[13]();
}

/* Configure PIO interrupt sources */
static void __initialize() {
	int i;
	for (i=0; i<ARD_NMAX_DIO; i++) {
		int_service_routine_ard_pin[i] = NULL;
		callback_ard_pin[i] = NULL;
	}
	int_service_routine_ard_pin[0] = int_service_routine0;
	int_service_routine_ard_pin[1] = int_service_routine1;
	int_service_routine_ard_pin[2] = int_service_routine2;
	int_service_routine_ard_pin[3] = int_service_routine3;
	int_service_routine_ard_pin[4] = int_service_routine4;
	int_service_routine_ard_pin[5] = int_service_routine5;
	int_service_routine_ard_pin[6] = int_service_routine6;
	int_service_routine_ard_pin[7] = int_service_routine7;
	int_service_routine_ard_pin[8] = int_service_routine8;
	int_service_routine_ard_pin[9] = int_service_routine9;
	int_service_routine_ard_pin[10] = int_service_routine10;
	int_service_routine_ard_pin[11] = int_service_routine11;
	int_service_routine_ard_pin[12] = int_service_routine12;
	int_service_routine_ard_pin[13] = int_service_routine13;
}


void attachInterrupt(uint32_t pin, void (*callback)(void), uint32_t mode)
{
	static int enabled = 0;
	LWGPIO_INT_MODE intMode = LWGPIO_INT_MODE_NONE;

	switch (mode) {
	case LOW: intMode = LWGPIO_INT_MODE_LOW;break;
	case HIGH: intMode = LWGPIO_INT_MODE_HIGH;break;
	case FALLING: intMode = LWGPIO_INT_MODE_FALLING;break;
	case RISING: intMode = LWGPIO_INT_MODE_RISING;break;
	//case CHANGE:
	}

	if (pin >= ARD_NMAX_DIO) return;
	if (!enabled) {
		__initialize();
		enabled = 1;
	}
	//printf("attachInterrupt() pin=%d  mode=%d\n", pin, mode);

/* //configured in pinmode()
// opening pins for input
if (!lwgpio_init(&ardDio[pin], arduinoToMqx_Pin[pin].pin, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
{
	printf("Initializing button GPIO as input failed.\n");
	_task_block();
}
    lwgpio_set_functionality(&ardDio[pin], arduinoToMqx_Pin[pin].mux);
#if defined(BSP_BUTTONS_ACTIVE_HIGH)
    lwgpio_set_attribute(&ardDio[pin], LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
#else
    lwgpio_set_attribute(&ardDio[pin], LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
#endif
*/

    /* enable gpio functionality for given pin, react on falling/rising edge */
    if (!lwgpio_int_init(&ardDio[pin], intMode))
    {
        printf("Initializing button GPIO for interrupt failed.\n");
        _task_block();
    }

    /* install gpio interrupt service routine */
    _int_install_isr(lwgpio_int_get_vector(&ardDio[pin]), int_service_routine_ard_pin[pin], (void *) &ardDio[pin]);
    /* set the interrupt level, and unmask the interrupt in interrupt controller */
    int32_t r1 = _bsp_int_init(lwgpio_int_get_vector(&ardDio[pin]), 3, 0, TRUE);
	printf("attachInterrupt() _bsp_int_init=%d\n", r1);

	callback_ard_pin[pin] = callback;

    /* enable interrupt on GPIO peripheral module */
    lwgpio_int_clear_flag(&ardDio[pin]);
    lwgpio_int_enable(&ardDio[pin], TRUE);
}

void detachInterrupt(uint32_t pin)
{
    /* disable interrupt on GPIO peripheral module */
    lwgpio_int_enable(&ardDio[pin], FALSE);
	callback_ard_pin[pin] = NULL;
}
