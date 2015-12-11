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

