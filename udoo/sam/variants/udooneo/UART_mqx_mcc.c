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

//#include <stdio.h>
//#include <string.h>

// this file is a wrapper for call mqx api without conflict with stdio.h, stdlib.h
// fio.h redefine write, read etc..

#include <mqx.h>
#include <bsp.h>
//#include <fio.h>
#include "mcc.h"
#include "mcc_config.h"
#include "mcc_common.h"
#include "mcc_api.h"
#include "mcc_mqx.h"
#include <string.h>

#include "log_mqx.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

//#define ARDUINO_SERIAL_DEBUG_RX
#define NODE_NUM			0ul
#define MCC_SEND_TIMEOUT	1000ul
static MCC_ENDPOINT    mqx_endpoint_m4 = {1,MCC_MQX_NODE_M4,MCC_MQX_PORT_M4};
static MCC_ENDPOINT    mqx_endpoint_a9 = {0,MCC_MQX_NODE_A9,MCC_MQX_PORT_A9};
static bool mccIsInitialized = FALSE;
#ifdef ARDUINO_SERIAL_DEBUG_RX
static _task_id serial_task_id_mcc = MQX_NULL_TASK_ID;
#endif

void mqx_uartclass_init_mcc (void)
{
    int             ret_value;

    ret_value = mcc_initialize(NODE_NUM);
    if(MCC_SUCCESS != ret_value) {
        printf("\n\n\nError, attempting to initialize the MCC library failed! Application is stopped now. Error code = %i\n", ret_value);
        mcc_destroy(NODE_NUM);
        _task_block();
    }

    //ret_value = mcc_get_info(node_num, &mcc_info);

    ret_value = mcc_create_endpoint(&mqx_endpoint_m4, MCC_MQX_PORT_M4);
    mccIsInitialized = TRUE;

#ifdef ARDUINO_SERIAL_DEBUG_RX
	// Create task for uart rx
	serial_task_id_mcc = _task_create(0, 6, 0);
	if (serial_task_id_mcc == MQX_NULL_TASK_ID) {
		printf("Could not create mqx_receive_task\n");
		_task_block();
	} else {
		printf("mqx_receive_task created \n");
	}
#endif

}

void mqx_uartclass_end_mcc (void)
{
	if (mccIsInitialized == TRUE) {
		mcc_destroy(NODE_NUM);
		mccIsInitialized = FALSE;
	}
}

void mqx_uartclass_flush_mcc (void)
{

}

int32_t mqx_uartclass_write_mcc (const uint8_t uc_data)
{
    int             ret_value;

	if (mccIsInitialized == TRUE) {
		ret_value = mcc_send(&mqx_endpoint_m4, &mqx_endpoint_a9, &uc_data, 1, MCC_SEND_TIMEOUT);
		if(MCC_SUCCESS != ret_value) {
			printf("\nMCC Error[%d], sending the message using the send function failed", ret_value);
			return (-1);
		}
		return (1);
	}
	return (0);
}

int32_t mqx_uartclass_write_buffer_mcc (const uint8_t *ptr, uint16_t len)
{
    int             ret_value;

	if (mccIsInitialized == TRUE) {
		//printf("mcc string = <%s> len = %d\r\n", ptr, len);
		ret_value = mcc_send(&mqx_endpoint_m4, &mqx_endpoint_a9, ptr, len+1, MCC_SEND_TIMEOUT);
		if(MCC_SUCCESS != ret_value) {
			printf("\nMCC Error[%d], sending the message using the send function failed", ret_value);
			return (-1);
		}
		return (len);
	}
	return (0);
}

#ifdef ARDUINO_SERIAL_DEBUG_RX
struct UARTClass;
void call_irq_handler (struct UARTClass* , uint8_t);
extern struct UARTClass SerialDebug;

void mqx_receive_task_mcc (uint32_t initial_data)
{
	uint8_t rxData;

//	_time_delay(5000);		// start after initialization from arduino main is made
	printf("mqx_receive_task_mcc is running!!\n");

	uint32_t testCounter = 0;

    while (TRUE)  {
/*
    	int32_t res = read(serial_dev, &rxData, 1);
    	printf("received char [%c]\n", rxData);
    	call_irq_handler(&SerialDebug, rxData);
*/
    	/*
    	testCounter++;
    	printf("testCounterRxTask=%d\n", testCounter);
    	_time_delay(500);
    	*/
    }
}
#endif
