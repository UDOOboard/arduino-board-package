/*
  Copyright (c) 2015-2018 UDOO

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

#pragma once

#ifdef __cplusplus
extern "C" {
void mqx_sched_yield (void);
void mqx_debug_int (int id, int d);
void mqx_debug_str (uint8_t *str);
}
#else
void mqx_sched_yield (void);
void mqx_debug_int (int id, int d);
void mqx_debug_str (uint8_t *str);
void mqx_debug_printf (const char* fmt, ...);
#endif
