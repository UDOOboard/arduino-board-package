/*HEADER**********************************************************************
*
* Copyright 2008 Freescale Semiconductor, Inc.
* Copyright 2011 Embedded Access Inc.
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
*   CPU specific ADC driver header file
*
*
*END************************************************************************/

#ifndef __lwadc_imxadc_h__
#define __lwadc_imxadc_h__

/*----------------------------------------------------------------------*/
/*
**                          CONSTANT DEFINITIONS
*/

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_HW_CHANNELS           4
#define ADC_NUM_DEVICES           2
#define LWADC_RESOLUTION_12BIT    0x1000
#define LWADC_RESOLUTION_10BIT    0x400
#define LWADC_RESOLUTION_8BIT     0x100
#define LWADC_RESOLUTION_DEFAULT  (LWADC_RESOLUTION_12BIT)
#define ADC_CDR_CDATA_MASK        0x00000FFF
#define ADC_DEV_SHIFT             (8)
#define ADC_DEV_MASK              (0xf00)
#define ADC_CHANNEL_MASK          (0xff)
    
#define ADC_INPUT(dev,channel)    (dev<<ADC_DEV_SHIFT | channel)
#define ADC_DEVICE(input)         (input>>ADC_DEV_SHIFT)
#define ADC_CHANNEL(input)        (input&ADC_CHANNEL_MASK)

#define ADC_INPUT_ADC1_AN0          ADC_INPUT(0,0)
#define ADC_INPUT_ADC1_AN1          ADC_INPUT(0,1)
#define ADC_INPUT_ADC1_AN2          ADC_INPUT(0,2)
#define ADC_INPUT_ADC1_AN3          ADC_INPUT(0,3)

#define ADC_INPUT_ADC2_AN0          ADC_INPUT(1,0)
#define ADC_INPUT_ADC2_AN1          ADC_INPUT(1,1)
#define ADC_INPUT_ADC2_AN2          ADC_INPUT(1,2)
#define ADC_INPUT_ADC2_AN3          ADC_INPUT(1,3)

typedef enum {
    LWADC_CLK_BUSCLK,     /* selects BUSCLK */
    LWADC_CLK_BUSCLK2,    /* selects BUSCLK/2 */
    LWADC_CLK_BUSCLK_ANY, /* selects BUSCLK or BUSCLK/2 */
    LWADC_CLK_ALTERNATE,
    LWADC_CLK_ASYNC
} LWADC_CLOCK_SOURCE;

typedef enum {
    LWADC_DIV_1 = 0,
    LWADC_DIV_2 = 1,
    LWADC_DIV_4 = 2,
    LWADC_DIV_8 = 3,
    LWADC_DIV_ANY = -1 /* selects automatically the fastest one */
} LWADC_CLOCK_DIV;

typedef enum {
    LWADC_LPC_LOW =    ADC_CFG_ADLPC_MASK, /* use low power of ADC (reduces max. ADCCLK frequency) */
    LWADC_LPC_NORMAL = 0                    /* use normal power of ADC */
} LWADC_LPC;

typedef enum {
    LWADC_HSC_NORMAL = ADC_CFG_ADHSC_MASK, /* use normal speed */
    LWADC_HSC_HIGH = 0                      /* use high speed */
} LWADC_HSC;

typedef enum {
    LWADC_PDB_COMP1OUT = 0,   /* Comparator 1 output trigger */
    LWADC_PDB_COMP2OUT = 4,   /* Comparator 2 output trigger */
    LWADC_PDB_EXTRIG   = 16,  /* External event trigger */
    LWADC_PDB_SWTRIG   = 28   /* Software trigger */
} LWADC_PDB_TRIGSEL;


typedef struct lwadc_init_struct {
    /* The number of ADC peripheral, use adc_t enum from PSP */
    uint8_t ADC_NUMBER;

    /* The clock source */
    LWADC_CLOCK_SOURCE CLOCK_SOURCE;

    /* The clock divisor for ADC */
    LWADC_CLOCK_DIV CLOCK_DIV;

    /* ADC high speed control, see ADC_HSC enum */
    LWADC_HSC SPEED;

    /* ADC low power control, see ADC_LPC enum */
    LWADC_LPC POWER;

    /* The calibration data pointer */
    uint8_t *CALIBRATION_DATA_PTR;

    /* ADC interrupt vector */
    uint32_t ADC_VECTOR;

    /* ADC interrupt vector */
    uint32_t ADC_PRIORITY;
    
    uint32_t REFERENCE;
}LWADC_INIT_STRUCT, * LWADC_INIT_STRUCT_PTR;

typedef struct adc_context {
    const LWADC_INIT_STRUCT *   init_ptr;
    ADC_MemMapPtr               adc_ptr;
    uint32_t                     mcr;
    uint32_t                     channels;
    uint32_t                     default_numerator;
    uint32_t                     default_denominator;
}ADC_CONTEXT, * ADC_CONTEXT_PTR;

typedef struct lwadc_struct {
    ADC_CONTEXT_PTR             context_ptr;
    uint32_t                     input;
    uint32_t                     numerator;
    uint32_t                     denominator;
}LWADC_STRUCT, * LWADC_STRUCT_PTR;

typedef enum {
    LWADC_RESOLUTION=1,
    LWADC_REFERENCE,
    LWADC_FREQUENCY,
    LWADC_DIVIDER,
    LWADC_DIFFERENTIAL,
    LWADC_POWER_DOWN,
    LWADC_NUMERATOR ,
    LWADC_DENOMINATOR,
    LWADC_DEFAULT_NUMERATOR ,
    LWADC_DEFAULT_DENOMINATOR,
    LWADC_FORMAT,
    LWADC_INPUT_CONVERSION_ENABLE
} LWADC_ATTRIBUTE;

#define LWADC_FORMAT_LEFT_JUSTIFIED     1
#define LWADC_FORMAT_RIGHT_JUSTIFIED    2


typedef uint32_t LWADC_VALUE, * LWADC_VALUE_PTR;

extern bool _lwadc_init( const LWADC_INIT_STRUCT * init_ptr);
extern bool _lwadc_init_input( LWADC_STRUCT_PTR lwadc_ptr, uint32_t input);
extern bool _lwadc_read_raw( LWADC_STRUCT_PTR lwadc_ptr,  LWADC_VALUE_PTR outSample);
extern bool _lwadc_read( LWADC_STRUCT_PTR lwadc_ptr, LWADC_VALUE_PTR outSample);
extern bool _lwadc_wait_next( LWADC_STRUCT_PTR lwadc_ptr);
extern bool _lwadc_read_average( LWADC_STRUCT_PTR lwadc_ptr, uint32_t num_samples, LWADC_VALUE_PTR outSample);
extern bool _lwadc_set_attribute( LWADC_STRUCT_PTR lwadc_ptr, LWADC_ATTRIBUTE attribute, uint32_t value);
extern bool _lwadc_get_attribute( LWADC_STRUCT_PTR lwadc_ptr, LWADC_ATTRIBUTE attribute, uint32_t *value_ptr);


#ifdef __cplusplus
}
#endif

#endif
