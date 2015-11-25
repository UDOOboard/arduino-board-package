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


    printf ("Wire.begin log....... ... ");
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
    if(I2C_OK == ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_MASTER_MODE, NULL))
    {
        printf("OK\n");
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

    printf ("Clear statistics ... ");
    if(I2C_OK == ioctl(i2c_fd[i2cId], IO_IOCTL_I2C_CLEAR_STATISTICS, NULL))
    {
        printf("OK\n");
    }
    else
    {
        printf("ERROR\n");
    }

    printf("Get statistics ... ");
    if(I2C_OK == ioctl(i2c_fd[i2cId], IO_IOCTL_I2C_GET_STATISTICS, (void *)&stats))
    {
        printf("OK\n  Interrupts:  %d\n", stats.INTERRUPTS);
        printf("  Rx packets:  %d\n", stats.RX_PACKETS);
        printf("  Tx packets:  %d\n", stats.TX_PACKETS);
        printf("  Tx lost arb: %d\n", stats.TX_LOST_ARBITRATIONS);
        printf("  Tx as slave: %d\n", stats.TX_ADDRESSED_AS_SLAVE);
        printf("  Tx naks:     %d\n", stats.TX_NAKS);
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

	result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &address);

    result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_REPEATED_START, NULL);
    //result = ioctl (i2c_dev, IO_IOCTL_I2C_SET_RX_REQUEST, &n);

	readed = fread(ptrRx, 1, n, i2c_fd[i2cId]);
//	fflush(i2c_dev);
	if (sendStop) {
		result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_STOP, NULL);
	}
	return (readed);
}

int32_t mqx_towire_endTransmission(uint8_t i2cId, uint8_t address, uint8_t quantity, uint8_t sendStop, uint8_t *ptrTx)
{
    _mqx_int result = I2C_OK;

	result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &address);
	result = fwrite(ptrTx, 1, quantity, i2c_fd[i2cId]);
	fflush(i2c_fd[i2cId]);
	if (sendStop) {
		result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_STOP, NULL);
	}
	return (result);
}

int32_t mqx_towire_setClock(uint8_t i2cId, uint32_t fr) {

	_mqx_int result = I2C_OK;

	result = ioctl (i2c_fd[i2cId], IO_IOCTL_I2C_SET_BAUD, &fr);

	return (result);
}
