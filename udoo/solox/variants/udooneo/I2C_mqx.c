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

#include <mqx.h>
#include <bsp.h>
#include <fio.h>

#include "log_mqx.h"

#if ! BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif

//#define	MQX_LOG_I2C

#define NMAX_I2C					2
// i2c driver name
#define ARDUINO_I2C_NAME			"ii2c2:"
#define MOTION_I2C_NAME			 	"ii2c4:"

extern const IMX_I2C_INIT_STRUCT 	_bsp_i2c2_init;
extern const IMX_I2C_INIT_STRUCT 	_bsp_i2c4_init;

typedef struct mqx_i2c_info
{
	IMX_I2C_INIT_STRUCT_PTR		initPtr;
	uint8_t						*namePtr;
} MQX_I2C_INFO, * MQX_I2C_INFO_PTR;

const MQX_I2C_INFO _mqx_i2c_info[NMAX_I2C] =
{
	{&_bsp_i2c2_init, ARDUINO_I2C_NAME},
	{&_bsp_i2c4_init, MOTION_I2C_NAME}
};

static MQX_FILE_PTR i2c_fd[NMAX_I2C] = {NULL};

void mqx_towire_begin (uint8_t i2cId)
{
	_imx_i2c_int_install(_mqx_i2c_info[i2cId].namePtr, _mqx_i2c_info[i2cId].initPtr);
	i2c_fd[i2cId] = fopen (_mqx_i2c_info[i2cId].namePtr, NULL);
	if(i2c_fd[i2cId] == NULL )
	{
		/* device could not be opened */
		printf("\nFatal Error: I2C Device \"%s\" open fail.\n", _mqx_i2c_info[i2cId].namePtr);
		_task_block();
	}
	else {
		printf("\nI2C Device \"%s\" open OK.\n", _mqx_i2c_info[i2cId].namePtr);
	}

#ifdef MQX_LOG_I2C
    I2C_STATISTICS_STRUCT stats;
    _mqx_int              param;
    //, result, c;
    //unsigned char        *buffer;


    printf ("Wire.begin log....... ... \n");
    printf ("Get current baud rate ... ");
    if(I2C_OK == ioctl(i2c_fd[i2cId], IO_IOCTL_I2C_GET_BAUD, &param))
    {
        printf("%d\n", param);
    }
    else
    {
        printf("ERROR\n");
    }

    printf("Set master mode ... ");
    if(I2C_OK == ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_GET_MODE, &param))
    {
        printf("%d\n", param);
    }
    else
    {
        printf("ERROR\n");
    }

    printf("Get current mode ... ");
    if (I2C_OK == ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_GET_MODE, &param))
    {
        printf("0x%02x\n", param);
    }
    else
    {
        printf("ERROR\n");
    }

    param = 0x00;
    printf("Get station address ... ");
    if(I2C_OK == ioctl(i2c_fd[i2cId], IO_IOCTL_I2C_GET_STATION_ADDRESS, &param))
    {
        printf("0x%02x\n", param);
    }
    else
    {
        printf("ERROR\n");
    }
    printf("Get current state ... ");
    if (I2C_OK == ioctl(i2c_fd[i2cId], IO_IOCTL_I2C_GET_STATE, &param))
    {
        printf("0x%02x\n", param);
    }
    else
    {
        printf("ERROR\n");
    }
#endif
}

void mqx_towire_end (uint8_t i2cId)
{
	// Wait for any outstanding data to be sent
	if (i2c_fd[i2cId] != NULL) {
		fflush (i2c_fd[i2cId]);
		fclose(i2c_fd[i2cId]);

		int32_t error_code = _io_dev_uninstall(_mqx_i2c_info[i2cId].namePtr);
		if (error_code != IO_OK) {
			printf("Error uninstalling %s.\n", _mqx_i2c_info[i2cId].namePtr);
			_task_block();
		}
		printf("Uninstall %s.\n", _mqx_i2c_info[i2cId].namePtr);
	}
}

void mqx_towire_flush (uint8_t i2cId)
{
	fflush (i2c_fd[i2cId]);
}

int32_t mqx_towire_requestFrom(uint8_t i2cId, uint8_t address, uint8_t quantity, uint8_t sendStop, uint8_t *ptrRx)
{
	// perform blocking read into buffer
	int readed = 0;
	int n = quantity;
    _mqx_int result = I2C_OK;

    //fflush(i2c_fd[i2cId]);

    result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_REPEATED_START, NULL);
    result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_RX_REQUEST, &n);

	readed = fread(ptrRx, 1, n, i2c_fd[i2cId]);

	if (sendStop) {
		result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_STOP, NULL);
	}

#ifdef MQX_LOG_I2C
	int32_t i;
	printf ("I2C readed ");
	for (i=0; i<readed; i++)
		printf ("[%02X]", ptrRx[i]);
	printf ("\n");
#endif
	return (readed);
}

int32_t mqx_towire_endTransmission(uint8_t i2cId, uint8_t address, uint8_t quantity, uint8_t sendStop, uint8_t *ptrTx)
{
    _mqx_int result = I2C_OK;

	result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &address);
#ifdef MQX_LOG_I2C
	if (I2C_OK != result) {
		printf ("IO_IOCTL_I2C_SET_DESTINATION_ADDRESS - Error = [%d]\n", result);
	}
#endif
	result = fwrite(ptrTx, 1, quantity, i2c_fd[i2cId]);
#ifdef MQX_LOG_I2C
	if (0 == result) {
		printf ("I2C fwrite - Error = [%d]\n", result);
	}
#endif
	fflush(i2c_fd[i2cId]);
	if (sendStop) {
		result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_STOP, NULL);
		if (I2C_OK != result) {
			printf ("IO_IOCTL_I2C_STOP - Error = [%d]\n", result);
		}
	}
	return (result);
}

int32_t mqx_towire_setClock(uint8_t i2cId, uint32_t fr) {

	_mqx_int result = I2C_OK;

	result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_BAUD, &fr);

	return (result);
}

void mqx_towire_uninstall (void)
{
	int i;

	for (i=0; i<NMAX_I2C; i++) {
		mqx_towire_end(i);
	}
}
