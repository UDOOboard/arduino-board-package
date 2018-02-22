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
uint32_t mqx_hwtimer_get_us (void);
void mqx_init_hwtimer1 (void);
void mqx_deinit_hwtimer1 (void);
}
#else
uint32_t mqx_hwtimer_get_us (void);
void mqx_init_hwtimer1 (void);
void mqx_deinit_hwtimer1 (void);
#endif
