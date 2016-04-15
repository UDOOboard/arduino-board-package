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
static void test_task (uint32_t);
extern void mqx_mccuart_receive_task (uint32_t);

//#define USER_TASK_ENABLED
#ifdef USER_TASK_ENABLED
static void arduino_user_task1 (uint32_t);
static void arduino_user_task2 (uint32_t);
static void arduino_user_task3 (uint32_t);
#endif

//#define MQX_LOG_TT
#define ARDUINO_SERIAL_DEBUG_RX

// ----------------------------------------------------------------------------------------------
// if a task with high priority make a loop without delay or other wait,
// then tasks with lower priority are blocked, also if _sched_yield() is called in the loop !!!!
// ----------------------------------------------------------------------------------------------
const TASK_TEMPLATE_STRUCT  MQX_template_list[] =
{
    /* Task Index, 	Function,  				Stack, 	Priority, 	Name,   	Attributes,          	Param, Time Slice */
    { 1,			main_task,				1500,	8,			"main",				MQX_AUTO_START_TASK,	0,     0 },
    { 2,			arduino_loop_task,		1500,	9,			"arduino_loop",		0,						0,     0 },
    { 3,			mqx_uart_receive_task,	1500,	9,			"uartrx",			0,						0,     0 },
    { 4,			arduino_yield_task,		1500,	9,			"arduino_yield",	0,						0,     0 },
    { 5,			test_task,				1500,	9,			"test",				0,						0,     0 },
#ifdef ARDUINO_SERIAL_DEBUG_RX
    { 6,			mqx_mccuart_receive_task,	1500,	9,			"mccrx",			0,						0,     0 },
#endif
#ifdef USER_TASK_ENABLED
    { 7,			arduino_user_task1,		1500,	9,			"user_task1",		0,						0,     0 },
    { 8,			arduino_user_task2,		1500,	9,			"user_task2",		0,						0,     0 },
    { 9,			arduino_user_task3,		1500,	9,			"user_task3",		0,						0,     0 },
#endif
    { 0 }
};

static void test_task
    (
        uint32_t initial_data
    )
{
	uint32_t testCounter = 0;

    printf("test_task is running!!\n");

    while (TRUE)  {
    	testCounter++;
    	printf("test_task=%d  initial_data=%d\n", testCounter, initial_data);
    	_time_delay(500);
    }
}

static void arduino_yield_task
    (
        uint32_t initial_data
    )
{

    printf("arduino_yield_task is running!!\n");

    while (TRUE)  {
    	yield();
    }
}

static void arduino_loop_task
(
        uint32_t initial_data
)
{
	uint32_t testCounter = 0;

    printf("arduino_loop_task is running!!\n");

    while (TRUE)  {
    	_sched_yield();
    	loop();
    	serialEventRun();
/*
    	testCounter++;
    	printf("testCounterArdTask=%d\n", testCounter);
    	_time_delay(100);
*/
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
    _task_id created_task_id = MQX_NULL_TASK_ID;
    bool endSketch = false;

    printf("\n\nmain_task is running...........\n");

    // arduino init
    init();
    setup();

    // Create task for arduino loop()
	created_task_id = _task_create(0, 2, 0);
	if (created_task_id == MQX_NULL_TASK_ID) {
		printf("\n Could not create arduino_loop_task\n");
		_task_block();
	} else {
		printf("arduino_loop_task created \n");
	}

#ifdef MQX_LOG_TT
	// Create test task
	created_task_id = _task_create(0, 5, 0);
	if (created_task_id == MQX_NULL_TASK_ID) {
		printf("\n Could not create test task\n");
		_task_block();
	} else {
		printf("test task created \n");
	}


	created_task_id = _task_create(0, 5, 1);
	if (created_task_id == MQX_NULL_TASK_ID) {
		printf("\n Could not create test task second time\n");
		_task_block();
	} else {
		printf("test task created second time\n");
	}

#endif


	// Create task for arduino_yield
	created_task_id = _task_create(0, 4, 0);
	if (created_task_id == MQX_NULL_TASK_ID) {
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

	_time_delay(100);
	do {
		if (*((uint8_t *)0xbff0ffff) == 0xAA)
			endSketch = true;
		_time_delay(100);
	}while (!endSketch);
	//*((uint8_t *)0xbff0ffff) = 0; not work fine
	printf("mqx_exit !!\n");
	_time_delay(100);
	_mqx_exit(1);

	printf("main-task blocked !!\n");
	_task_block();
}

