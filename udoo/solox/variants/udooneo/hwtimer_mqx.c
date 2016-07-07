#include <mqx.h>
#include <bsp.h>

#include "log_mqx.h"

HWTIMER hwtimer1;                               //hwtimer handle

uint32_t mqx_hwtimer_get_us (void)
{
    return (hwtimer_get_ticks(&hwtimer1) << 2);
}

// this timer is used to get elapsed microseconds
// the resolution is 4 usec
void init_hwtimer1 (void)
{

    /* Initialization of hwtimer1*/
    printf("\nInitialization of hwtimer1 ");
    if (MQX_OK != hwtimer_init(&hwtimer1, &BSP_HWTIMER1_DEV, BSP_HWTIMER1_ID, (BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX + 1)))
    {
        printf(" FAILED!\n");
    }
    else
    {
        printf(" OK\n");
    }

    printf("Try to set period %d us to hwtimer1\n", 4);
    hwtimer_set_period(&hwtimer1, BSP_HWTIMER1_SOURCE_CLK, 4);	// if setting period < 4 not work fine
    printf("Read frequency from hwtimer1 : %d Hz\n", hwtimer_get_freq(&hwtimer1));
    printf("Read period from hwtimer1    : %d us\n", hwtimer_get_period(&hwtimer1));
    printf("Read modulo from hwtimer1    : %d\n", hwtimer_get_modulo(&hwtimer1));
    /* Start hwtimer1*/
    printf("Start hwtimer1\n");
    hwtimer_callback_block(&hwtimer1);
    hwtimer_start(&hwtimer1);
}

void deinit_hwtimer1 (void)
{

    printf("Deinit hwtimer1\n");
    hwtimer_stop(&hwtimer1);
    hwtimer_deinit(&hwtimer1);
}
