/*HEADER**********************************************************************
*
* Copyright 2014 Freescale Semiconductor, Inc.
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
*
*   multicore low power management APIs header file
*
*
*END************************************************************************/

#ifndef __lpm_mcore_h__
#define __lpm_mcore_h__

/*
 * Macro definition
 */
#define STATUS_NORMAL_RUN               0
#define STATUS_LOWPOWER_RUN             1

#define NVIC_GIC_OFFSET                 16
#define REGISTER_PEER_WAKEUP_MASK       0x55555000
#define MSG_FMT_INT_NO_OFFSET           4

#define LPM_MCORE_MU_CHANNEL            0

#define WAKEUP_ENABLE                   1
#define WAKEUP_DISABLE                  0
#define WAKEUP_REGISTER_SUCCESS         1
#define WAKEUP_REGISTER_FAILURE         0

#define STATUS_LPRUN                    0x2222BBBB
#define STATUS_HIRUN                    0x2222CCCC
#define PEER_RESPONSE_HI_OK             0xFFFF6666
#define PEER_FREQ_CHANGE_READY          0xFFFF7777
/*
 * API function declaration
 */
#ifdef __cplusplus
extern "C" {
#endif

/*
 * mcore lpm init API
 */
void _io_mcore_lpm_init(void);

/*
 * mcore lpm API to get current power status
 */
uint32_t _io_mcore_lpm_get_status(void);

/*
 * mcore lpm API to set power status
 */
void _io_mcore_lpm_set_status(uint32_t status);

/*
 * mcore lpm API to register peer wakeup interrupt
 */
uint32_t _io_mcore_lpm_register_peer_wakeup(uint32_t int_no, uint32_t enable);

/*
 * mcore lpm API to enter TCM WFI
 */
void _io_mcore_lpm_wfi(void);

#ifdef __cplusplus
}
#endif

#endif
