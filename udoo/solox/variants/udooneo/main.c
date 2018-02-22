/*HEADER**********************************************************************
*
* Copyright 2013 Freescale Semiconductor, Inc.
* Copyright (c) 2015-2018 UDOO
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
*END************************************************************************/

#include "mqx.h"
#include "bsp.h"
#include "log_mqx.h"
#include "Arduino.h"

#include "udoomqx.h"

void serialEventRun(void);

/* Function prototypes */
extern void init(void);
static void main_task(uint32_t);
extern void mqx_uart_rx_task(uint32_t);
static void arduino_loop_task(uint32_t);
static void arduino_yield_task(uint32_t);
static void exit_task(uint32_t);
extern void mqx_mccuart_rx_task(uint32_t);
extern void mqx_uartclass_end_mcc(void);
extern void deinit_hwtimer1(void);
extern void detachGPIO_Interrupt(void);
extern void mqx_towire_uninstall(void);
extern void mqx_spi_end(void);

//#define USER_TASK_ENABLED
#ifdef USER_TASK_ENABLED
static void arduino_user_task1(uint32_t);
static void arduino_user_task2(uint32_t);
static void arduino_user_task3(uint32_t);
#endif

//#define MQX_LOG_TT
#define ARDUINO_SERIAL_DEBUG_RX

extern int SKETCH_RUNNING;
int SKETCH_RUNNING = 1;

// ----------------------------------------------------------------------------------------------
// if a task with high priority make a loop without delay or other wait,
// then tasks with lower priority are blocked, also if _sched_yield() is called in the loop !!!!
// ----------------------------------------------------------------------------------------------
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
/*   TaskIndex,      Function,               Stack, Priority, Name,             Attributes,           Param,  TimeSlice  */
	{TASK_MAIN,      main_task,              1500,   8,       "main",           MQX_AUTO_START_TASK,  0,      0          },
	{TASK_LOOP,      arduino_loop_task,      1500,   9,       "arduino_loop",   0,                    0,      0          },
	{TASK_UARTRX,    mqx_uart_rx_task,       1500,   9,       "uart_rx",        0,                    0,      0          },
	{TASK_YELD,      arduino_yield_task,     1500,   9,       "arduino_yield",  0,                    0,      0          },
	{TASK_EXIT,      exit_task,              1500,   8,       "exit",           0,                    0,      0          },
#ifdef ARDUINO_SERIAL_DEBUG_RX
	{TASK_MCCRX,     mqx_mccuart_rx_task,    1500,   9,       "mccrx",          0,                    0,      0          },
#endif
#ifdef USER_TASK_ENABLED
	{TASK_USER1,     arduino_user_task1,     1500,   9,       "user_task1",     0,                    0,      0          },
	{TASK_USER2,     arduino_user_task2,     1500,   9,       "user_task2",     0,                    0,      0          },
	{TASK_USER3,     arduino_user_task3,     1500,   9,       "user_task3",     0,                    0,      0          },
#endif
	{ 0 }
};

static _task_id loop_task_id = MQX_NULL_TASK_ID;
static _task_id yield_task_id = MQX_NULL_TASK_ID;
static _task_id exit_task_id = MQX_NULL_TASK_ID;
static _task_id main_task_id = MQX_NULL_TASK_ID;

static void exit_task(uint32_t initial_data)
{
	printf("TASK %s running...\n", __FUNCTION__);

	AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE07_EXIT_TASK_RUN);

	bool endSketch = false;
	do {
		if (*((uint8_t *)ADDR_SHARED_BYTE_FOR_M4STOP) == 0xAA)
			endSketch = true;
		_time_delay(100);
	} while (!endSketch);

	printf("Received Stop M4 Sketch!\n");
	SKETCH_RUNNING = 0;

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

	AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE12_MQX_EXIT);
        printf("->->-> Quitting MQX\n");
        _time_delay(100);

	_mqx_exit(1);
	do {}while(1);
}

static void arduino_yield_task(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);
    AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE09_ARDUINO_YIELD_TASK_RUN);

    while (SKETCH_RUNNING) {
    	_sched_yield();
    	yield();
    }

    RemoveMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE09_ARDUINO_YIELD_TASK_RUN);
    _task_block();
}

static void arduino_loop_task(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);
    AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE08_ARDUINO_LOOP_TASK_RUN);

    while (SKETCH_RUNNING) {
    	_sched_yield();
    	loop();
    	serialEventRun();
    }

    RemoveMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE08_ARDUINO_LOOP_TASK_RUN);
    _task_block();
}

static void arduino_user_task1(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);

    while (SKETCH_RUNNING) {
    	user_task1();
    }

    _task_block();
}

static void arduino_user_task2(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);

    while (SKETCH_RUNNING) {
    	user_task2();
    }

    _task_block();
}

static void arduino_user_task3(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);

    while (SKETCH_RUNNING) {
    	user_task3();
    }

    _task_block();
}

/******************************************************************************
*
* Task Name    : main_task
*
******************************************************************************/

static void main_task(uint32_t initial_data)
{
    printf("TASK %s running...\n", __FUNCTION__);
    AddMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE06_MAIN_TASK_RUN);

    // Create exit task
    printf("Creating exit task...\n");
    main_task_id = _task_create(0, TASK_EXIT, 0);
    if (main_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: Could not create exit task!\n");
        _task_block();
    }

    // arduino init
    printf("==========================\n");
    printf("%s: calling init()...\n", __FUNCTION__);
    init();
    printf("==========================\n");
    printf("%s: calling setup()...\n", __FUNCTION__);
    setup();
    printf("==========================\n");

    // Create task for arduino loop()
    printf("%s: starting task arduino_loop_task...\n", __FUNCTION__);
    loop_task_id = _task_create(0, TASK_LOOP, 0);
    if (loop_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: could not create arduino_loop_task!\n");
        _task_block();
    }

    // Create task for arduino_yield
    printf("%s: starting task arduino_yield_task...\n", __FUNCTION__);
    yield_task_id = _task_create(0, TASK_YELD, 0);
    if (yield_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: could not create arduino_yeld_task!\n");
        _task_block();
    }

#ifdef USER_TASK_ENABLED
    // Create user task1
    printf("%s: starting task user_task1...\n", __FUNCTION__);
    created_task_id = _task_create(0, TASK_USER1, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: could not create user_task1!\n");
        _task_block();
    }

    // Create user task2
    printf("%s: starting task user_task2...\n", __FUNCTION__);
    created_task_id = _task_create(0, TASK_USER2, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: could not create user_task2!\n");
        _task_block();
    }

    // Create user task3
    printf("%s: starting task user_task3...\n", __FUNCTION__);
    created_task_id = _task_create(0, TASK_USER3, 0);
    if (created_task_id == MQX_NULL_TASK_ID) {
        printf("ERROR: could not create user_task3!\n");
        _task_block();
    }
#endif

    printf("%s: task blocked\n", __FUNCTION__);
    RemoveMsk_Shared_RAM(ADDR_SHARED_TRACE_FLAGS, TRACE06_MAIN_TASK_RUN);
    _task_block();
}

