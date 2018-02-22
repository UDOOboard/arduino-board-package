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
#include <fio.h>
#include "udoomqx.h"
#include "log_mqx.h"

extern int SKETCH_RUNNING;

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in \
	user_config.h. Please recompile BSP with this option.
#endif

// serial
#define ARDUINO_SERIAL_QUEUE_SIZE	256
#define ARDUINO_SERIAL_BAUD_RATE	115200
#define UART5

#ifdef UART3
#define ARDUINO_SERIAL_NAME 		"ittyc:"
static IMX_UART_INIT_STRUCT _arduino_serial_init = {
   /* queue size         */ ARDUINO_SERIAL_QUEUE_SIZE,
   /* Channel            */ 3,
   /* Clock Speed        */ BSP_PLL3_UART_CLOCK,
   /* Baud rate          */ ARDUINO_SERIAL_BAUD_RATE,
   /* RX/TX Int vect     */ 44, //INT_UART3,
   /* ERR Int vect       */ 0, //INT_UART1_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4,
};
#endif

#ifdef UART5
#define ARDUINO_SERIAL_NAME 		"ittye:"
static IMX_UART_INIT_STRUCT _arduino_serial_init = {
   /* queue size         */ ARDUINO_SERIAL_QUEUE_SIZE,
   /* Channel            */ 5,
   /* Clock Speed        */ BSP_PLL3_UART_CLOCK,
   /* Baud rate          */ ARDUINO_SERIAL_BAUD_RATE,
   /* RX/TX Int vect     */ 46, //INT_UART5,
   /* ERR Int vect       */ 0, //INT_UART1_ERR,
   /* RX/TX priority     */ 3,
   /* ERR priority       */ 4,
};
#endif

static MQX_FILE_PTR serial_dev = NULL;
static _task_id serial_task_id = MQX_NULL_TASK_ID;

void StampaStatistiche(void)
{
	int32_t r;
	IMX_UART_INFO_STRUCT stat;

	r = ioctl(serial_dev,IO_IOCTL_SERIAL_GET_STATS, &stat);
	printf("IO_IOCTL_SERIAL_GET_STATS=%ld\n", r);
	printf ("INTERRUPTS = %ld\n", stat.INTERRUPTS);
	printf ("RX_CHARS = %ld\n", stat.RX_CHARS);
	printf ("TX_CHARS = %ld\n", stat.RX_CHARS);
	printf ("RX_BREAKS = %ld\n", stat.RX_BREAKS);
	printf ("RX_PARITY_ERRORS = %ld\n", stat.RX_PARITY_ERRORS);
	printf ("FRAMING_ERRORS = %ld\n", stat.RX_FRAMING_ERRORS);
	printf ("RX_OVERRUNS = %ld\n", stat.RX_OVERRUNS);
	printf ("RX_DROPPED_INPUT = %ld\n", stat.RX_DROPPED_INPUT);
}

void mqx_uartclass_init (const uint32_t dwBaudRate, const uint32_t modeReg)
{
	int32_t r=-1;
	uint32_t flag = 0;

	// must be used ioctl, bat now not work !!!!!!!!
	_arduino_serial_init.BAUD_RATE = dwBaudRate;
	 r = _imx_uart_int_install(ARDUINO_SERIAL_NAME, &_arduino_serial_init, _arduino_serial_init.QUEUE_SIZE);
	printf("_imx_uart_int_install=%ld\n", r);
	serial_dev = fopen (ARDUINO_SERIAL_NAME, IO_SERIAL_RAW_IO);
	if( serial_dev == NULL )
	{
		/* device could not be opened */
		printf("\nFatal Error: Serial Device \"%s\" open fail.\n", ARDUINO_SERIAL_NAME);
		_task_block();
	}

//    Mode_8N1 = 0,
//    Mode_8E1 = 1,
//    Mode_8O1 = 2,
//    Mode_8M1 = 3,
//    Mode_8S1 = 4
	switch (modeReg) {
	case 1:
		flag = IO_SERIAL_PARITY_EVEN;
		ioctl(serial_dev,IO_IOCTL_SERIAL_SET_FLAGS, &flag);
		break;
	case 2:
		flag = IO_SERIAL_PARITY_ODD;
		ioctl(serial_dev,IO_IOCTL_SERIAL_SET_FLAGS, &flag);
		break;
	}

#ifdef MQX_LOG_UART
	bool f=FALSE;
	int32_t bb;

	printf ("Serial0.begin log....... ... \r");

	r = ioctl(serial_dev,IO_IOCTL_SERIAL_DISABLE_RX, &f);
	printf("IO_IOCTL_SERIAL_DISABLE_RX=%ld\n", r);
	r = ioctl(serial_dev,IO_IOCTL_CLEAR_STATS, 0);
	printf("IO_IOCTL_CLEAR_STATS=%ld\n", r);
	r = ioctl(serial_dev,IO_IOCTL_SERIAL_GET_BAUD, &bb);
	printf("IO_IOCTL_SERIAL_GET_BAUD=%ld bb=%ld\n", r, bb);
	StampaStatistiche();
#endif

	// Create task for uart rx
	printf("Creating mqx_uart_rx_task...\n");
	serial_task_id = _task_create(0, TASK_UARTRX, 0);
	if (serial_task_id == MQX_NULL_TASK_ID) {
		printf("ERROR: Could not create mqx_uart_rx_task!\n");
		_task_block();
	}

	return;
}

void mqx_uartclass_end (void)
{
    // Wait for any outstanding data to be sent

	if (serial_task_id != MQX_NULL_TASK_ID) {
		_task_destroy(serial_task_id);
		serial_task_id = MQX_NULL_TASK_ID;
	}

	fflush (serial_dev);
	fclose(serial_dev);

	int32_t error_code = _io_dev_uninstall(ARDUINO_SERIAL_NAME);
	if (error_code != IO_OK) {
		printf("Error uninstalling %s.\n", ARDUINO_SERIAL_NAME);
		_task_block();
	}
}

void mqx_uartclass_flush (void)
{
	fflush (serial_dev);
}

int32_t mqx_uartclass_write (const uint8_t uc_data)
{
	return (write(serial_dev, (void *)&uc_data, 1));
}

int32_t mqx_uartclass_write_buffer (const uint8_t *ptr, uint16_t len)
{
	return (write(serial_dev, (uint8_t *)ptr, len));
}

struct UARTClass;
void call_irq_handler (struct UARTClass* , uint8_t);
extern struct UARTClass Serial0;

void mqx_uart_rx_task(uint32_t initial_data)
{
    uint8_t rxData;

    AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE11_UART_RX_TASK_RUN);
    printf("TASK %s running...\n", __FUNCTION__);

    uint32_t testCounter = 0;

    while (SKETCH_RUNNING) {

    	int32_t res = read(serial_dev, &rxData, 1);
    	call_irq_handler(&Serial0, rxData);

    	/*
    	testCounter++;
    	printf("testCounterRxTask=%d\n", testCounter);
    	_time_delay(500);
    	*/
    }

    RemoveMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE11_UART_RX_TASK_RUN);
    _task_block();
}
