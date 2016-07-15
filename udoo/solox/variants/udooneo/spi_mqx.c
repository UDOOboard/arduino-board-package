#include <mqx.h>
#include <bsp.h>
//#include <fio.h>
#include <spi_bsp_mqx.h>
#include "spi_mqx.h"

#include "log_mqx.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

/*
#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif
*/

// not work !!!, see mqx_spi_begin()
const char *spiChannelsNoCS[] =
{
		"spi1:0",
		"spi2:0",
		"spi3:0",
		"spi4:0",
		"spi5:0"
};

const char *spiChannelsCS[] =
{
		"spi1:",
		"spi2:",
		"spi3:",
		"spi4:",
		"spi5:"
};

const char *device_mode[] =
{
    "SPI_DEVICE_MASTER_MODE",
    "SPI_DEVICE_SLAVE_MODE",
};

const char *clock_mode[] =
{
    "SPI_CLK_POL_PHA_MODE0",
    "SPI_CLK_POL_PHA_MODE1",
    "SPI_CLK_POL_PHA_MODE2",
    "SPI_CLK_POL_PHA_MODE3"
};

/*
static const ECSPI_INIT_STRUCT _bsp_ecspi5_init = {
    5,                            // SPI channel
    CLK_ECSPI5                    // Relevant module clock source
};

const SPI_INIT_STRUCT _bsp_spi5_init = {
    &_spi_ecspi_devif,             // Low level driver interface
    &_bsp_ecspi5_init,             // Low level driver init data
    {                              // Default parameters:
        10000000,                  // Baudrate
        SPI_CLK_POL_PHA_MODE0,     // Mode
        MAX_FRAME_SIZE,            // Frame size in bits
        0,                         // Chip select
        0,                         // Attributes
        0xFFFFFFFF                 // Dummy pattern
    }
*/

extern const SPI_INIT_STRUCT _bsp_spi5_init;
static MQX_FILE_PTR spifd = NULL;

void mqx_spi_begin (uint8_t csPin)
{
    _io_spi_install((char *)spiChannelsCS[SPI_INTERFACE-1], &_bsp_spi5_init);

	// IMPORTANT: ---------------------------------------------------
	//spiChannelsNoCS not work. For change cs in manual mode, I modified init_gpio.c in bsp source
	// --------------------------------------------------------------
	/* Open the SPI driver */
	if (csPin == 0)
		spifd = fopen (spiChannelsNoCS[SPI_INTERFACE-1], NULL);
	else
		// automatic CS, arduino pin11 J6, ECSPI5.SS
		spifd = fopen (spiChannelsCS[SPI_INTERFACE-1], NULL);

    if (NULL == spifd)
    {
        printf ("Error opening SPI driver!\n");
        _time_delay (200L);
        _task_block ();
    }

    /* Set transfer mode */
    /* default init driver
#ifdef MQX_LOG
    printf ("%s Setting transfer mode to %s ... ", spiChannels[SPI_INTERFACE-1], device_mode[SPI_DEVICE_MASTER_MODE]);
#endif
    if (SPI_OK == ioctl (spifd, IO_IOCTL_SPI_SET_TRANSFER_MODE, &param))
    {
#ifdef MQX_LOG
        printf ("OK\n");
#endif
    }
    else
    {
#ifdef MQX_LOG
        printf ("ERROR\n");
#endif
    }
    */
}

/* Set a baud rate */
void mqx_spi_set_baud (uint32_t baud)
{

    if (NULL != spifd)
    {
        printf ("Changing the baud rate to %d Hz ... ", baud);
        if (SPI_OK == ioctl (spifd, IO_IOCTL_SPI_SET_BAUD, &baud))
        {
            printf ("OK\n");
        }
        else
        {
            printf ("KO\n");
        }
    }
}

/* Set data mode */
void mqx_spi_set_data_mode (uint32_t mode)
{

    if (NULL != spifd)
    {
        printf ("Setting clock mode to %s ... ", clock_mode[mode]);
        if (SPI_OK == ioctl (spifd, IO_IOCTL_SPI_SET_MODE, &mode))
        {
            printf ("OK\n");
        }
        else
        {
            printf ("KO\n");
        }
    }
}

/* Set data mode */
// arduino: LSBFIRST = 0, MSBFIRST=1
// mqx:     SPI_DEVICE_LITTLE_ENDIAN(0x8000), SPI_DEVICE_BIG_ENDIAN(0x0001)
void mqx_spi_set_bit_order (uint32_t bitOrder)
{
uint32_t endian = 1;

	if (bitOrder == 0)
		endian = SPI_DEVICE_LITTLE_ENDIAN;
	else
		endian = SPI_DEVICE_BIG_ENDIAN;

	if (NULL != spifd)
    {
        printf ("Setting bit order mode to %x ... ", endian);
        if (SPI_OK == ioctl (spifd, IO_IOCTL_SPI_SET_ENDIAN, &endian))
        {
            printf ("OK\n");
        }
        else
        {
            printf ("KO\n");
        }
    }
}

/* Set frame size, there is not bitlen (8, 16) !!!*/
void mqx_spi_set_frame_size (uint32_t len)
{

	if (NULL != spifd)
    {
        printf ("Setting frame size to %d ... ", len);
        if (SPI_OK == ioctl (spifd, IO_IOCTL_SPI_SET_FRAMESIZE, &len))
        {
            printf ("OK\n");
        }
        else
        {
            printf ("KO\n");
        }
    }
}

/*FUNCTION*---------------------------------------------------------------
*
* Function Name : tx_rx_burst
* Comments  : This function send and receive one byte to SPI bus
* Return:
*         Status read.
*
*END*----------------------------------------------------------------------*/

_mqx_int mqx_tx_rx_burst(uint8_t *tx_buffer, uint8_t *rx_buffer, uint32_t len)
{
    _mqx_int result;
    SPI_READ_WRITE_STRUCT rw;

    /* Write instruction and read status */
    rw.BUFFER_LENGTH = len;
    rw.WRITE_BUFFER = (char *)tx_buffer;
    rw.READ_BUFFER = (char *)rx_buffer;

    result = ioctl (spifd, IO_IOCTL_SPI_READ_WRITE, &rw);
    if (result != SPI_OK)
    {
        printf ("ERROR (tx)\n");
    }
    else
    {
        return MQX_OK;
    }

    return MQX_ERROR;
}

void mqx_spi_end (void)
{

	// Wait for any outstanding data to be sent
	if (spifd != NULL) {
		fflush (spifd);
		fclose(spifd);

		int32_t error_code = _io_dev_uninstall((char *)spiChannelsCS[SPI_INTERFACE-1]);
		if (error_code != IO_OK) {
			printf("Error uninstalling %s.\n", spiChannelsCS[SPI_INTERFACE-1]);
			_task_block();
		}
		printf("Uninstall %s.\n", spiChannelsCS[SPI_INTERFACE-1]);
	}
}
