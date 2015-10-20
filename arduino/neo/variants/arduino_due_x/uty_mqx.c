#include <mqx.h>
#include <bsp.h>

#ifndef MQX_LOG
#define MQX_LOG
#endif

#include "log_mqx.h"

void mqx_sched_yield (void)
{
	_sched_yield();
}

void mqx_debug_int (int id, int d)
{
	printf("mqx_debug_int: id=%ld value=%ld\n", id, d);
}

void mqx_debug_str (uint8_t *str)
{
	printf(str);
}

