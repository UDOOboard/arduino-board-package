/*HEADER**********************************************************************
*
* Copyright 2013 Freescale Semiconductor, Inc.
*
* This software is owned or controlled by Freescale Semiconductor.
* Use of this software is governed by the Freescale MQX RTOS License
* distributed with this Material.
* See the MQX_RTOS_LICENSE file distributed for more details.
*
* Brief License Summary:
* This software is provided in source form for you to use free of charge,
* but it is not open source software. You are allowed to use this software
* but you cannot redistribute it or derivative works of it in source form.
* The software may be used only in connection with a product containing
* a Freescale microprocessor, microcontroller, or digital signal processor.
* See license agreement file for full license terms including other
* restrictions.
*****************************************************************************
*
* Comments:
*   This file contains the source for the gpio example program.
*
*
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"

#include "log_mqx.h"
#include "Arduino.h"

void serialEventRun(void);

/* Function prototypes */
extern void init( void );
static void main_task(uint32_t);
extern void mqx_uart_receive_task(uint32_t);
static void arduino_loop_task(uint32_t);
static void arduino_yield_task (uint32_t);
static void exit_task (uint32_t);
extern void mqx_mccuart_receive_task (uint32_t);
extern void mqx_uartclass_end_mcc (void);
extern void deinit_hwtimer1 (void);
extern void detachGPIO_Interrupt(void);
extern void mqx_towire_uninstall (void);
extern void mqx_spi_end (void);

//#define USER_TASK_ENABLED
#ifdef USER_TASK_ENABLED
static void arduino_user_task1 (uint32_t);
static void arduino_user_task2 (uint32_t);
static void arduino_user_task3 (uint32_t);
#endif

//#define MQX_LOG_TT
#define ARDUINO_SERIAL_DEBUG_RX
#define ADDR_SHARED_BYTE_FOR_M4STOP 		0xbff0ffff	// byte wrote by m4_stop tool to force M4 scketch to secure exit

// ----------------------------------------------------------------------------------------------
// if a task with high priority make a loop without delay or other wait,
// then tasks with lower priority are blocked, also if _sched_yield() is called in the loop !!!!
// ----------------------------------------------------------------------------------------------
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
	/*      TaskIndex,               Function,                  Stack,  Priority,  Name,             Attributes,           Param,  TimeSlice  */
	{       1,                       main_task,                 1500,   8,         "main",           MQX_AUTO_START_TASK,  0,      0          },
	{       2,                       arduino_loop_task,         1500,   9,         "arduino_loop",   0,                    0,      0          },
	{       3,                       mqx_uart_receive_task,     1500,   9,         "uartrx",         0,                    0,      0          },
	{       4,                       arduino_yield_task,        1500,   9,         "arduino_yield",  0,                    0,      0          },
	{       5,                       exit_task,                 1500,   8,         "exit",           0,                    0,      0          },
#ifdef ARDUINO_SERIAL_DEBUG_RX
	{       6,                       mqx_mccuart_receive_task,  1500,   9,         "mccrx",          0,                    0,      0          },
#endif
#ifdef USER_TASK_ENABLED
	{       7,                       arduino_user_task1,        1500,   9,         "user_task1",     0,                    0,      0          },
	{       8,                       arduino_user_task2,        1500,   9,         "user_task2",     0,                    0,      0          },
	{       9,                       arduino_user_task3,        1500,   9,         "user_task3",     0,                    0,      0          },
#endif
	{ 0 }
};

static _task_id loop_task_id = MQX_NULL_TASK_ID;
static _task_id yield_task_id = MQX_NULL_TASK_ID;
static _task_id exit_task_id = MQX_NULL_TASK_ID;
static _task_id main_task_id = MQX_NULL_TASK_ID;

static void exit_task
    (
        uint32_t initial_data
    )
{

	AddMsk_Shared_RAM (ADDR_SHARED_TRACE_FLAGS, MSK7_SHARED_TRACE_FLAGS);

	printf("exit_task is running!!\n");
	bool endSketch = false;
	do {
		if (*((uint8_t *)ADDR_SHARED_BYTE_FOR_M4STOP) == 0xAA)
			endSketch = true;
		_time_delay(100);
	}while (!endSketch);
	printf("Received Stop M4 Sketch!\n");

	// disable gpio interrupt
	detachGPIO_Interrupt();

	// destroy tasks
	_task_destroy(loop_task_id);
	printf("_task_destroy(loop_task_id)\n");
	_task_destroy(yield_task_id);
	printf("_task_destroy(yield_task_id)\n");
	_time_delay(100);

	deinit_hwtimer1();
	mqx_uartclass_end_mcc ();
	mqx_towire_uninstall ();
	mqx_spi_end ();

	printf("call _mqx_exit\n");
	_time_delay(100);

	AddMsk_Shared_RAM (ADDR_SHARED_TRACE_FLAGS, MSK12_SHARED_TRACE_FLAGS);

	_mqx_exit(1);
	do {}while(1);
}

static void arduino_yield_task
    (
        uint32_t initial_data
    )
{

	AddMsk_Shared_RAM (ADDR_SHARED_TRACE_FLAGS, MSK9_SHARED_TRACE_FLAGS);

    printf("arduino_yield_task is running!!\n");

    while (TRUE)  {
    	_sched_yield();
    	yield();
    }
}

static void arduino_loop_task
(
        uint32_t initial_data
)
{
	uint32_t testCounter = 0;

	AddMsk_Shared_RAM (ADDR_SHARED_TRACE_FLAGS, MSK8_SHARED_TRACE_FLAGS);

    printf("arduino_loop_task is running!!\n");

    while (TRUE)  {
    	_sched_yield();
    	loop();
    	serialEventRun();
    }
}

static void arduino_user_task1
    (
        uint32_t initial_data
    )
{

    printf("arduino_user_task1 is running!!\n");

    while (TRUE)  {
    	user_task1();
    }
}

static void arduino_user_task2
    (
        uint32_t initial_data
    )
{

    printf("arduino_user_task2 is running!!\n");

    while (TRUE)  {
    	user_task2();
    }
}

static void arduino_user_task3
    (
        uint32_t initial_data
    )
{

    printf("arduino_user_task3 is running!!\n");

    while (TRUE)  {
    	user_task3();
    }
}

/******************************************************************************
*
* Task Name    : main_task
*
******************************************************************************/

static void main_task
    (
        uint32_t initial_data
    )
{

    AddMsk_Shared_RAM (ADDR_SHARED_TRACE_FLAGS, MSK6_SHARED_TRACE_FLAGS);

    printf("\n\nmain_task is running...........\n");

    // Create exit task
    main_task_id = _task_create(0, 5, 0);
    if (main_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create exit task\n");
	    _task_block();
    } else {
	    printf("Exit task created \n");
    }

    // arduino init
    init();
    setup();

    // Create task for arduino loop()
    loop_task_id = _task_create(0, 2, 0);
    if (loop_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create arduino_loop_task\n");
	    _task_block();
    } else {
	    printf("arduino_loop_task created \n");
    }

    // Create task for arduino_yield
    yield_task_id = _task_create(0, 4, 0);
    if (yield_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create arduino_yield_task\n");
	    _task_block();
    } else {
	    printf("arduino_yield_task created \n");
    }

#ifdef USER_TASK_ENABLED
    // Create user task1
    created_task_id = _task_create(0, 7, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create user_task1\n");
	    _task_block();
    } else {
	    printf("user task1 created \n");
    }

    // Create user task2
    created_task_id = _task_create(0, 8, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create user_task2\n");
	    _task_block();
    } else {
	    printf("user task2 created \n");
    }

    // Create user task3
    created_task_id = _task_create(0, 9, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
	    printf("\n Could not create user_task2\n");
	    _task_block();
    } else {
	    printf("user task2 created \n");
    }
#endif


    printf("main-task blocked !!\n");
    _task_block();
}

