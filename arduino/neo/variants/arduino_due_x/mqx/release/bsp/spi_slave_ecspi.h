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
*   required for the ECSPI slave driver.
*
*
*END************************************************************************/

#ifndef __SPI_SLAVE_ECSPI_H__
#define __SPI_SLAVE_ECSPI_H__

#include <bsp.h>
#include <stdint.h>

/*! @addtogroup spi_slave_driver*/
/*! @{*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*
** SPI clock polarity and phase (IO_IOCTL_SPI_XXX_MODE)
*/
#define SPI_CPHA_MASK                      (0x01)
#define SPI_CPOL_MASK                      (0x02)

#define SPI_CLK_POL_PHA_MODE0              (0x00)                            /* Inactive SPICLK low, sample on leading edge */
#define SPI_CLK_POL_PHA_MODE1              (SPI_CPHA_MASK)                   /* Inactive SPICLK low, sample on trailing edge */
#define SPI_CLK_POL_PHA_MODE2              (SPI_CPOL_MASK)                   /* Inactive SPICLK high, sample on leading edge */
#define SPI_CLK_POL_PHA_MODE3              (SPI_CPOL_MASK | SPI_CPHA_MASK)   /* Inactive SPICLK high, sample on trailing edge */
#define SPI_CLK_POL_PHA_MODE_MASK          (SPI_CPOL_MASK | SPI_CPHA_MASK)


/* SPI Error Codes */
#define SPI_OK                             (0x00)
#define SPI_ERROR_MODE_INVALID             (SPI_ERROR_BASE | 0x01)
#define SPI_ERROR_TRANSFER_MODE_INVALID    (SPI_ERROR_BASE | 0x02)
#define SPI_ERROR_BAUD_RATE_INVALID        (SPI_ERROR_BASE | 0x03)
#define SPI_ERROR_ENDIAN_INVALID           (SPI_ERROR_BASE | 0x04)
#define SPI_ERROR_CHANNEL_INVALID          (SPI_ERROR_BASE | 0x05)
#define SPI_ERROR_DEINIT_FAILED            (SPI_ERROR_BASE | 0x06)
#define SPI_ERROR_INVALID_PARAMETER        (SPI_ERROR_BASE | 0x07)
#define SPI_ERROR_FRAMESIZE_INVALID        (SPI_ERROR_BASE | 0x08)


/*--------------------------------------------------------------------------*/
/*
**                    DATATYPE DECLARATIONS
*/

/*
** ECSPI_SLAVE_INFO_STRUCT
** Structure keep user configuration and run time state information.
*/
typedef struct ecspi_slave_info_struct
{ 
    /* --------------------------- User's section --------------------------- */
    /* Peripheral instance. */
    uint32_t INSTANCE;

    /* Size of single SPI data frame in bits. */
    uint32_t FRAME_SIZE;

    /* CS signal for the transfer. */
    uint32_t CS;

    /* SS_POL, Slave select active state: 0-low, 1-high */
    uint32_t SS_POL;

    /* SS_CTL, Burst end by: 0-number of bits, 1-SS edge */
    uint32_t SS_CTL;

    /* Clock polarity and phase setting. */
    uint32_t MODE;

    /* ECSPI slave driver callback */
    _mqx_int (*CALLBACK)(void *app_data_ptr, uint32_t *tx_data_ptr, uint32_t *rx_data_ptr);

    /* Pointer to application data for callback */
    void *APP_DATA_PTR;

    /* --------------------------- System section --------------------------- */
    /* Register access structure */
    ECSPI_MemMapPtr ECSPI_REG_PTR;

    /* Clock node */
    void    *ECSPI_CLOCK;
} ECSPI_SLAVE_INFO_STRUCT, * ECSPI_SLAVE_INFO_STRUCT_PTR;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*FUNCTION**********************************************************************
*
* Function Name    : ecspi_slave_init
* Returned Value   : MQX status code
* Comments         : 
*    Initializes the ECSPI module
*    Turns on the clock to the module. 
*    Enables the device and interrupts.
*
* param1: Pointer to driver info structure.
*
*END***************************************************************************/
_mqx_int ecspi_slave_init(ECSPI_SLAVE_INFO_STRUCT_PTR info_ptr);


/*FUNCTION**********************************************************************
*
* Function Name    : ecspi_slave_shutdown
* Returned Value   : MQX status code
* Comments         : 
*    Deinitializes the device.
*    Clears the control register and turns off the clock to the module.
*
* param1: Pointer to driver info structure.
*
*END***************************************************************************/
_mqx_uint ecspi_slave_shutdown(ECSPI_SLAVE_INFO_STRUCT_PTR info_ptr);


#if defined(__cplusplus)
}
#endif

#endif /* __SPI_SLAVE_ECSPI_H__*/
