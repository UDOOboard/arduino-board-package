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

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


// this file is a wrapper for call mqx api without conflict with stdio.h, stdlib.h
// fio.h redefine write, read etc..

/*
Modificato per RPMSG !!!!!!!!!!!!!!!!!!
*/

#include <mqx.h>
#include <bsp.h>
#include <string.h>

#include "rpmsg/rpmsg_rtos.h"

#include "log_mqx.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

#define NODE_NUM			0ul

//#define MCC_SEND_TIMEOUT	1000ul
//static MCC_ENDPOINT    mqx_endpoint_m4 = {1,MCC_NODE_M4,MCC_PORT_M4};
//static MCC_ENDPOINT    mqx_endpoint_a9 = {0,MCC_NODE_A9,MCC_PORT_A9};

//#define USR_ENDPT 127
//#define TTY_ENDPT 126

extern int SKETCH_RUNNING;
extern int RPMSG_INIT; // 0=uninitialized; 1=initialized; 3+=initialized+rxcleared

struct remote_device *rdev = NULL;
struct rpmsg_channel *app_chnl = NULL;

static _task_id serial_task_id_rpmsg = MQX_NULL_TASK_ID;

typedef struct rpmsg_uart_message
{
   uint8_t  DATA[RPMSG_BUFFER_SIZE];
} RPMSG_UART_MESSAGE;

void mqx_uartclass_init_rpmsg (void)
{
    int             ret_value;

    // rpmsg driver init 
    ret_value = rpmsg_rtos_init(0 /*REMOTE_CPU_ID*/, &rdev, RPMSG_MASTER, &app_chnl);
	// mqx_debug_int(1000, ret_value);

	// mqx_debug_printf("Name service handshake is done, M4 has setup a rpmsg channel [%d ---> %d] rp_ept=%d\r\n", app_chnl->src, app_chnl->dst);

    if(RPMSG_SUCCESS != ret_value)
    {
      mqx_debug_printf("\n\n\nError, rpmsg init failed! Task is stopped now. Error code = %i\n", ret_value);
      _task_block();
    }

	if (RPMSG_INIT == 0) RPMSG_INIT = 1;

	// Create task for uart rx
	serial_task_id_rpmsg = _task_create(0, 6, 0);
	if (serial_task_id_rpmsg == MQX_NULL_TASK_ID) {
		mqx_debug_printf("Could not create mqx_receive_task\n");
		_task_block();
	} else {
		printf("mqx_receive_task created \n");
	}
}

void mqx_uartclass_end_rpmsg (void)
{
	if (RPMSG_INIT > 0) {
		_task_destroy(6);
		_task_destroy(100);
		printf("ho distrutto i task 6 e 100 di rpmsg\n");
		// do not call deinit, otherwise M4 is locked on an HW sema4!
		// rpmsg_rtos_deinit(rdev);
		RPMSG_INIT = 0;
	}
}

void mqx_uartclass_flush_rpmsg (void)
{

}

int32_t mqx_uartclass_write_rpmsg (const uint8_t uc_data)
{
  int             ret_value;

  if (RPMSG_INIT > 0) {
    // Send the message 
	ret_value = rpmsg_rtos_send(app_chnl->rp_ept, &uc_data, sizeof(uc_data), app_chnl->dst);
    if(RPMSG_SUCCESS != ret_value) {
      printf("\nRPMSG Error[%d], sending the message using the send function failed", ret_value);
      return (-1);
    }
    return (1);
  }
  return (0);
}

int32_t mqx_uartclass_write_buffer_rpmsg (const uint8_t *ptr, uint16_t len)
{
  int             ret_value;

  if (RPMSG_INIT > 0) {
    // Send the whole buffer
	ret_value = rpmsg_rtos_send(app_chnl->rp_ept, ptr, len, app_chnl->dst);
    if(RPMSG_SUCCESS != ret_value) {
      printf("\nRPMSG Error[%d], sending the message using the send function failed", ret_value);
      return (-1);
    }
    return (len);
  }
  return (0);
}

struct UARTClass;
void call_irq_handler (struct UARTClass* , uint8_t);
extern struct UARTClass Serial;

void mqx_mccuart_receive_task (uint32_t initial_data)
{
	int32_t ret_value, received_bytes, i;
	RPMSG_UART_MESSAGE msg;
	printf("Task mqx_rpmsguart_receive_task is running!\n");

    while (SKETCH_RUNNING)  {

		ret_value = rpmsg_rtos_recv(app_chnl->rp_ept, &msg, &received_bytes, sizeof(msg), NULL, 0xFFFFFFFF);

		if (RPMSG_SUCCESS == ret_value && received_bytes > 0) {

		    // printf("RPMSG received a msg from A9 endpoint, len=%d\n", received_bytes);

			if (RPMSG_INIT == 3 || RPMSG_INIT == 7) {
				if (RPMSG_INIT == 3 && received_bytes == 1 && msg.DATA[i] == '0') {
					// printf("Skipping 0 in HANDSHAKE!\n");
					RPMSG_INIT = 7;
					continue;
				} else {
					if (RPMSG_INIT == 7) {
						if (received_bytes == 9 && msg.DATA[i] == 'x') {
							// printf("Skipping HANDSHAKE (2)!\n");
							RPMSG_INIT = 3;
							continue;
						} else {
							call_irq_handler(&Serial, '0');
						}
					}
				}
			}

			if (RPMSG_INIT >= 3) {
				// printf("%d RECEIVED: data[0]=%c\n", RPMSG_INIT, msg.DATA[0]);
				RPMSG_INIT = 15;
				for (i=0; i<received_bytes; i++) {
				    call_irq_handler(&Serial, msg.DATA[i]);
				}
			} else {
				if (received_bytes == 9 || received_bytes == 10) {
					// printf("Skipping HANDSHAKE (1)!\n");
					RPMSG_INIT = 3;
				}
			}
		}
    }

	_task_block();
}

