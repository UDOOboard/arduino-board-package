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
#include "log_mqx.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define ARD_DIO0		                    (LWGPIO_PORT4 | LWGPIO_PIN10)
#define ARD_DIO0_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN10_GPIO)
#define ARD_DIO1		                    (LWGPIO_PORT4 | LWGPIO_PIN11)
#define ARD_DIO1_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN11_GPIO)
#define ARD_DIO2		                    (LWGPIO_PORT4 | LWGPIO_PIN8)
#define ARD_DIO2_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN8_GPIO)
#define ARD_DIO3		                    (LWGPIO_PORT5 | LWGPIO_PIN15)
#define ARD_DIO3_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN15_GPIO)
#define ARD_DIO4		                    (LWGPIO_PORT5 | LWGPIO_PIN14)
#define ARD_DIO4_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN14_GPIO)
#define ARD_DIO5		                    (LWGPIO_PORT5 | LWGPIO_PIN13)
#define ARD_DIO5_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN13_GPIO)
#define ARD_DIO6		                    (LWGPIO_PORT5 | LWGPIO_PIN12)
#define ARD_DIO6_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN12_GPIO)
#define ARD_DIO7		                    (LWGPIO_PORT5 | LWGPIO_PIN21)
#define ARD_DIO7_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN21_GPIO)
#define ARD_DIO8		                    (LWGPIO_PORT4 | LWGPIO_PIN9)
#define ARD_DIO8_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN9_GPIO)
#define ARD_DIO9		                    (LWGPIO_PORT5 | LWGPIO_PIN20)
#define ARD_DIO9_MUX_GPIO                   (LWGPIO_MUX_PORT5_PIN20_GPIO)
#define ARD_DIO10		                    (LWGPIO_PORT4 | LWGPIO_PIN7)
#define ARD_DIO10_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN7_GPIO)
#define ARD_DIO11		                    (LWGPIO_PORT4 | LWGPIO_PIN5)
#define ARD_DIO11_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN5_GPIO)
#define ARD_DIO12		                    (LWGPIO_PORT4 | LWGPIO_PIN4)
#define ARD_DIO12_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN4_GPIO)
#define ARD_DIO13		                    (LWGPIO_PORT4 | LWGPIO_PIN6)
#define ARD_DIO13_MUX_GPIO                   (LWGPIO_MUX_PORT4_PIN6_GPIO)

const DioPinMap arduinoToMqx_Pin[ARD_NMAX_DIO] = {
		{ARD_DIO0, 		ARD_DIO0_MUX_GPIO},			// 0
		{ARD_DIO1, 		ARD_DIO1_MUX_GPIO},			// 1
		{ARD_DIO2, 		ARD_DIO2_MUX_GPIO},			// 2
		{ARD_DIO3, 		ARD_DIO3_MUX_GPIO},			// 3
		{ARD_DIO4, 		ARD_DIO4_MUX_GPIO},			// 4
		{ARD_DIO5, 		ARD_DIO5_MUX_GPIO},			// 5
		{ARD_DIO6, 		ARD_DIO6_MUX_GPIO},			// 6
		{ARD_DIO7, 		ARD_DIO7_MUX_GPIO},			// 7
		{ARD_DIO8, 		ARD_DIO8_MUX_GPIO},			// 8
		{ARD_DIO9, 		ARD_DIO9_MUX_GPIO},			// 9
		{ARD_DIO10, 	ARD_DIO10_MUX_GPIO},		// 10
		{ARD_DIO11, 	ARD_DIO11_MUX_GPIO},		// 11
		{ARD_DIO12, 	ARD_DIO12_MUX_GPIO},		// 12
		{ARD_DIO13, 	ARD_DIO13_MUX_GPIO},		// 13
};

LWGPIO_STRUCT ardDio[ARD_NMAX_DIO];

extern void pinMode( uint32_t ulPin, uint32_t ulMode )
{

	if (ulPin >= ARD_NMAX_DIO) return;
	switch (ulMode)
    {
        case INPUT:
            // opening pins for input
            if (!lwgpio_init(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].pin, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
            {
				printf("Initializing Pin%d as GPIO output failed.\n", ulPin);
                _task_block();
            	return;
            }
            /* swich pin functionality (MUX) to GPIO mode */
            lwgpio_set_functionality(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].mux);
            uint32_t gf = lwgpio_get_functionality(&ardDio[ulPin]);
			printf("lwgpio_get_functionality inputPin%d = %08X\n", ulPin, gf);
            bool sa = lwgpio_set_attribute(&ardDio[ulPin], LWGPIO_ATTR_PULL_DOWN, LWGPIO_AVAL_ENABLE);
			printf("lwgpio_set_attribute inputPin%d = %d\n", ulPin, sa);
        break ;

        case INPUT_PULLUP:
            // opening pins for input
            if (!lwgpio_init(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].pin, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE))
            {
            	printf("Initializing LED1 GPIO as output failed.\n");
                _task_block();
            	return;
            }
            /* swich pin functionality (MUX) to GPIO mode */
            lwgpio_set_functionality(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].mux);
            lwgpio_set_attribute(&ardDio[ulPin], LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE);
        break ;

        case OUTPUT:
            if (!lwgpio_init(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].pin, LWGPIO_DIR_OUTPUT, LWGPIO_VALUE_NOCHANGE))
            {
            	printf("Initializing LED1 GPIO as output failed.\n");
                _task_block();
            	return;
            }
            /* swich pin functionality (MUX) to GPIO mode */
            lwgpio_set_functionality(&ardDio[ulPin], arduinoToMqx_Pin[ulPin].mux);
        break ;

        default:
        break ;
    }
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
	if (ulPin >= ARD_NMAX_DIO) return;
	/* write logical 1 to the pin */
	lwgpio_set_value(&ardDio[ulPin], ulVal); /* set pin to 1 */
}

extern int digitalRead( uint32_t ulPin )
{

	if (ulPin >= ARD_NMAX_DIO) return (LOW);
    if (LWGPIO_VALUE_HIGH == lwgpio_get_value(&ardDio[ulPin]))
    	return (HIGH);
    else
    	return (LOW);

    return (LOW);
}


void PrintMessageOut(uint16_t s)
{
	printf("Write %d to pin[0-13]\n", s);
}

void PrintInputMessage0(uint16_t i, uint16_t stInputs)
{
	printf("Initial state for pin[%d] = %d\n", i, stInputs);
}

void PrintInputMessage(uint16_t i, uint16_t stInputs)
{
	printf("New state for pin[%d] = %d\n", i, stInputs);
}


#ifdef __cplusplus
}
#endif

