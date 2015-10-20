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
*   This file contains the definitions of constants and structures
*   required for the ECSPI driver
*
*
*END************************************************************************/

#ifndef __spi_ecspi_h__
#define __spi_ecspi_h__

#include "clk_api.h"

/*--------------------------------------------------------------------------*/
/*
**                    CONSTANT DEFINITIONS
*/

/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** ECSPI_INIT_STRUCT
**
** This structure defines the initialization parameters to be used
** when a spi port is initialized.
*/
typedef struct ecspi_init_struct
{
   /* SPI channel number */
   uint32_t CHANNEL;

   /* The input clock source of the module */
   CLOCK_NAME CLK_NAME;

} ECSPI_INIT_STRUCT, * ECSPI_INIT_STRUCT_PTR;

typedef const ECSPI_INIT_STRUCT * ECSPI_INIT_STRUCT_CPTR;


/*----------------------------------------------------------------------*/
/*
**              DEFINED VARIABLES
*/

extern const SPI_DEVIF_STRUCT _spi_ecspi_devif;


/*--------------------------------------------------------------------------*/
/*
**                        FUNCTION PROTOTYPES
*/

#ifdef __cplusplus
extern "C" {
#endif
void       *_bsp_get_ecspi_base_address(uint32_t channel);
uint32_t    _bsp_get_ecspi_vector(uint32_t channel);
CLOCK_NAME  _bsp_get_ecspi_clock_name(uint32_t channel);
#ifdef __cplusplus
}
#endif

#endif
