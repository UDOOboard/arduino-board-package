
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
* See license agreement file for full license terms including other restrictions.
*****************************************************************************
*
* Comments:
*
*   This is the MCC Message Unit driver definition file
*
*
*END************************************************************************/

#ifndef __MU__
#define __MU__

typedef void (*MU_CALLBACK)(void *);
#define MU_INT_PRIORITY 3

/* BSR Bit Fields */
#define MU_BSR_TE0_MASK                         0x800000u
#define MU_BSR_TE1_MASK                         0x400000u
#define MU_BSR_TE2_MASK                         0x200000u
#define MU_BSR_TE3_MASK                         0x100000u
#define MU_BSR_RF0_MASK                         0x8000000u
#define MU_BSR_RF1_MASK                         0x4000000u
#define MU_BSR_RF2_MASK                         0x2000000u
#define MU_BSR_RF3_MASK                         0x1000000u
#define MU_BSR_GIP0_MASK                        0x10000000u
#define MU_BSR_GIP1_MASK                        0x20000000u
#define MU_BSR_GIP2_MASK                        0x40000000u
#define MU_BSR_GIP3_MASK                        0x80000000u

/* BCR Bit Fields */
#define MU_BCR_BAF0_MASK                        0x1u
#define MU_BCR_BAF1_MASK                        0x2u
#define MU_BCR_BAF2_MASK                        0x4u
#define MU_BCR_GIR0_MASK                        0x10000u
#define MU_BCR_GIR1_MASK                        0x20000u
#define MU_BCR_GIR2_MASK                        0x40000u
#define MU_BCR_GIR3_MASK                        0x80000u
#define MU_BCR_TIE0_MASK                        0x800000u
#define MU_BCR_TIE1_MASK                        0x400000u
#define MU_BCR_TIE2_MASK                        0x200000u
#define MU_BCR_TIE3_MASK                        0x100000u
#define MU_BCR_RIE0_MASK                        0x8000000u
#define MU_BCR_RIE1_MASK                        0x4000000u
#define MU_BCR_RIE2_MASK                        0x2000000u
#define MU_BCR_RIE3_MASK                        0x1000000u
#define MU_BCR_GIE0_MASK                        0x10000000u
#define MU_BCR_GIE1_MASK                        0x20000000u
#define MU_BCR_GIE2_MASK                        0x40000000u
#define MU_BCR_GIE3_MASK                        0x80000000u

#ifdef __cplusplus
extern "C" {
#endif

void     mu_initialize(void);
void     mu_finalize(void);

uint32_t mu_rx(int channel);
uint32_t mu_rx_available(int channel);

void     mu_tx(int channel, uint32_t data);
uint32_t mu_tx_available(int channel);

void     mu_disable_rx_isr(int channel);
void     mu_enable_rx_isr(int channel, MU_CALLBACK callback, void *data);

void     mu_disable_tx_isr(int channel);
void     mu_enable_tx_isr(int channel, MU_CALLBACK callback, void *data);

void     mu_set_gp(int index);
void     mu_clear_gp(int index);
void     mu_disable_gp_isr(int index);
void     mu_enable_gp_isr(int index, MU_CALLBACK callback, void *data);

#ifdef __cplusplus
}
#endif

#endif /* __MU__ */
