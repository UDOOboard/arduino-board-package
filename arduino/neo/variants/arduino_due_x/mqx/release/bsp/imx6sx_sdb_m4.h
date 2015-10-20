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
*   This include file is used to provide information needed by
*   an application program using the kernel running on the
*   Freescale i.MX 6SoloX SDB Evaluation board.
*
*
*END************************************************************************/

#ifndef _imx6sx_sdb_m4_h_
#define _imx6sx_sdb_m4_h_  1

/*----------------------------------------------------------------------
**                  HARDWARE INITIALIZATION DEFINITIONS
*/

#define BSP_MAX_SHARE_CLOCK_NODE_CNT           (40)
/*
** Define the board type
*/
#define BSP_IMX6SX_SDB_M4                   1
#define BSP_NAME                            "IMX6SX_SDB_M4"

#ifdef __CC_ARM
#define __DEFAULT_INTERRUPT_STACK_SIZE      1024
#else
extern uint8_t __DEFAULT_INTERRUPT_STACK_SIZE[];
#endif

extern const vector_entry __vector_table[256];
extern vector_entry ram_vector[256];
#define __VECTOR_TABLE_ROM_START    ((_mqx_max_type)__vector_table)
#define __VECTOR_TABLE_RAM_START    ((_mqx_max_type)ram_vector)

/** MGCT: <category name="BSP Hardware Options"> */

/* Init startup clock configuration is CPU_CLOCK_CONFIG_0 */
#define BSP_CLOCK_SRC                   (24000000)
#define BSP_CORE_CLOCK                  (227000000)   /* 480 * 18 / 19 / 2 (PLL3 PFD3) */
#define BSP_BUS_CLOCK                   (132000000)   /* AHB clock: 396 / 3 (PLL2 PFD2) */
#define BSP_SYSTEM_CLOCK                (132000000)   /* AHB clock: 396 / 3 (PLL2 PFD2) */
#define BSP_IPG_CLOCK                   (BSP_SYSTEM_CLOCK / 2)

#define BSP_CORE_CLOCK_FIRC             (12000000)
#define BSP_BUS_CLOCK_FIRC              (6000000)
#define BSP_SYSTEM_CLOCK_FIRC           (6000000)
#define BSP_IPG_CLOCK_FIRC              (BSP_SYSTEM_CLOCK_FIRC / 2)

#define BSP_PLL3_UART_CLOCK             (80000000)
#define BSP_PLL3_ECSPI_CLOCK            (60000000)

/*
** The clock tick rate in miliseconds - be cautious to keep this value such
** that it divides 1000 well.
**
** MGCT: <option type="number" min="1" max="1000"/>
*/
#ifndef BSP_ALARM_FREQUENCY
    #define BSP_ALARM_FREQUENCY         (200)
//    #define BSP_ALARM_FREQUENCY         (1000) for 1msec tick
#endif

/*
** System timer definitions
*/
#define BSP_SYSTIMER_DEV                systick_devif
#define BSP_SYSTIMER_ID                 0
#define BSP_SYSTIMER_SRC_CLK            CM_CLOCK_SOURCE_CORE
#define BSP_SYSTIMER_ISR_PRIOR          2

/* We need to keep BSP_TIMER_INTERRUPT_VECTOR macro for tests and watchdog.
 * Will be removed after hwtimer expand to all platforms */
#define BSP_TIMER_INTERRUPT_VECTOR      INT_SysTick

/** MGCT: </category> */

/*
** Old clock rate definition in MS per tick, kept for compatibility
*/
#define BSP_ALARM_RESOLUTION            (1000 / BSP_ALARM_FREQUENCY)

/*
** Define the location of the hardware interrupt vector table
*/
#if MQX_ROM_VECTORS
    #define BSP_INTERRUPT_VECTOR_TABLE              ((uint32_t)__VECTOR_TABLE_ROM_START)
#else
    #define BSP_INTERRUPT_VECTOR_TABLE              ((uint32_t)__VECTOR_TABLE_RAM_START)
#endif

#ifndef BSP_FIRST_INTERRUPT_VECTOR_USED
    #define BSP_FIRST_INTERRUPT_VECTOR_USED     (0)
#endif

#ifndef BSP_LAST_INTERRUPT_VECTOR_USED
    #define BSP_LAST_INTERRUPT_VECTOR_USED      (143)
#endif

/*----------------------------------------------------------------------
**            Core Mutex
*/

/** MGCT: <category name="Core Mutex Options"> */

/*
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_CORE_MUTEX
    #define BSPCFG_CORE_MUTEX               1
#endif

/*
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_CORE_MUTEX_STATS
    #define BSPCFG_CORE_MUTEX_STATS         0
#endif

/*
** MGCT: <option type="number"/>
*/
#ifndef BSPCFG_CORE_MUTEX_PRIORITY
    #define BSPCFG_CORE_MUTEX_PRIORITY      3
#endif

/** MGCT: </category> */

/*
** RTC interrupt level
*/
#define BSP_RTC_INT_LEVEL                   (5)

/*
** LPM related
*/
#define BSP_LPM_DEPENDENCY_LEVEL_SERIAL_POLLED (30)
#define BSP_LPM_DEPENDENCY_LEVEL_SERIAL_INT    (31)

#define BSP_SHMEM_SEMAPHORE_NUMBER             (15)
// #define BSP_MAX_SHARE_CLOCK_NODE_CNT           (40)

/*-----------------------------------------------------------------------------
**                      GPIO
*/
// by fefr
/* SDB BOARD SW4 */
/* GPIO PORT1_18 */
//#define BSP_BUTTON1_PROMPT                  "SW4"
//#define BSP_BUTTON1                         (LWGPIO_PIN_CSI_DATA04)
//#define BSP_BUTTON1_MUX_GPIO                (LWGPIO_MUX_CSI_DATA04_GPIO)
//#define BSP_BUTTON1_MUX_IRQ                 (LWGPIO_MUX_CSI_DATA04_GPIO)

/* SDB BOARD SW5 */
/* GPIO PORT1_19 */
//#define BSP_BUTTON2_PROMPT                  "SW5"
//#define BSP_BUTTON2                         (LWGPIO_PIN_CSI_DATA05)
//#define BSP_BUTTON2_MUX_GPIO                (LWGPIO_MUX_CSI_DATA05_GPIO)
//#define BSP_BUTTON2_MUX_IRQ                 (LWGPIO_MUX_CSI_DATA05_GPIO)

/*
** HWTIMER specifications
*/
#define BSP_HWTIMER1_DEV                    epit_devif
#define BSP_HWTIMER1_SOURCE_CLK             (EPIT_CLOCK_IPG)
#define BSP_HWTIMER1_ID                     (1)
#define BSP_HWTIMER2_DEV                    epit_devif
#define BSP_HWTIMER2_SOURCE_CLK             (EPIT_CLOCK_IPG)
#define BSP_HWTIMER2_ID                     (2)

/* 32.768K Refrence Clock */
#define BSP_HWTIMER_LP_SOURCE_CLK           (EPIT_CLOCK_LP_CKIL)
#define BSP_HWTIMER_LP_REF_CLK_FREQ         32768

/*-----------------------------------------------------------------------------
**                      ECSPI
*/
#define BSP_ECSPI_INT_LEVEL                  (4)
#define BSP_SPI_MEMORY_CHANNEL               (5)

/*-----------------------------------------------------------------------------
**                      I2C
*/
#define BSP_I2C_CLOCK                       (BSP_IPG_CLOCK)
#define BSP_I2C1_ADDRESS                    (0x6E)
#define BSP_I2C2_ADDRESS                    (0x6F)
#define BSP_I2C3_ADDRESS                    (0x70)
#define BSP_I2C4_ADDRESS                    (0x71)

#define BSP_I2C1_BAUD_RATE                  (100000)
#define BSP_I2C2_BAUD_RATE                  (100000)
#define BSP_I2C3_BAUD_RATE                  (100000)
#define BSP_I2C4_BAUD_RATE                  (100000)

#define BSP_I2C1_MODE                       (I2C_MODE_MASTER)
#define BSP_I2C2_MODE                       (I2C_MODE_MASTER)
#define BSP_I2C3_MODE                       (I2C_MODE_MASTER)
#define BSP_I2C4_MODE                       (I2C_MODE_MASTER)

#define BSP_I2C1_INT_LEVEL                  (5)
#define BSP_I2C2_INT_LEVEL                  (5)
#define BSP_I2C3_INT_LEVEL                  (5)
#define BSP_I2C4_INT_LEVEL                  (5)

#define BSP_I2C1_RX_BUFFER_SIZE             (64)
#define BSP_I2C1_TX_BUFFER_SIZE             (64)
#define BSP_I2C2_RX_BUFFER_SIZE             (64)
#define BSP_I2C2_TX_BUFFER_SIZE             (64)
#define BSP_I2C3_RX_BUFFER_SIZE             (64)
#define BSP_I2C3_TX_BUFFER_SIZE             (64)
#define BSP_I2C4_RX_BUFFER_SIZE             (64)
#define BSP_I2C4_TX_BUFFER_SIZE             (64)

/*-----------------------------------------------------------------------------
**                      ADC
*/
#define ADC_MAX_MODULES                     (2)
#define BSP_ADC_INPUT_1                     (ADC_INPUT_ADC1_AN0)
#define BSP_ADC1_VECTOR_PRIORITY            (3)
#define BSP_ADC2_VECTOR_PRIORITY            (3)
#define BSP_PDB_VECTOR_PRIORITY             (3)
#define BSP_ADC_VREF_DEFAULT                (3300)
#define BSP_ADC_POTENTIOMETER_MAX           (3300)

#define BSP_DEFAULT_LWADC_MODULE            lwadc1_init


/*-----------------------------------------------------------------------------
**                      M_CAN
** BSP_MCAN_DEVICE can be defined as 1 or 2
*/
#define BSP_MCAN_DEVICE                (1)

/*-----------------------------------------------------------------------------
**                  IO DEVICE DRIVERS CONFIGURATION
*/

/** MGCT: <category name="I/O Subsystem"> */

/*
** Enable I/O subsystem features in MQX. No I/O drivers and file I/O will be
** possible without this feature.
**
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_IO_SUBSYSTEM
    #define BSPCFG_ENABLE_IO_SUBSYSTEM      1
#endif

/** MGCT: </category> */

/** MGCT: <category name="Default Driver Installation in BSP startup"> */

/** MGCT: <category name="UART1 Settings"> */

/*
** Polled TTY device (UART1)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYA
    #define BSPCFG_ENABLE_TTYA              0
#endif

/*
** Interrupt-driven TTY device (UART1)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYA
    #define BSPCFG_ENABLE_ITTYA             0
#endif

/*
** TTYA and ITTYA baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI1_BAUD_RATE
    #define BSPCFG_SCI1_BAUD_RATE           115200
#endif

/*
** TTYA and ITTYA buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI1_QUEUE_SIZE
    #define BSPCFG_SCI1_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/** MGCT: <category name="UART2 Settings"> */

/*
** Polled TTY device (UART2)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYB
    #define BSPCFG_ENABLE_TTYB              0
#endif

/*
** Interrupt-driven TTY device (UART2)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYB
    #define BSPCFG_ENABLE_ITTYB             1
#endif

/*
** TTYB and ITTYB baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI2_BAUD_RATE
    #define BSPCFG_SCI2_BAUD_RATE           115200
#endif

/*
** TTYB and ITTYB buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI2_QUEUE_SIZE
    #define BSPCFG_SCI2_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/** MGCT: <category name="UART3 Settings"> */

/*
** Polled TTY device (UART3)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYC
    #define BSPCFG_ENABLE_TTYC              0
#endif

/*
** Interrupt-driven TTY device (UART3)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYC
    #define BSPCFG_ENABLE_ITTYC             0
#endif

/*
** TTYC and ITTYC baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI3_BAUD_RATE
    #define BSPCFG_SCI3_BAUD_RATE           115200
#endif

/*
** TTYC and ITTYC buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI3_QUEUE_SIZE
    #define BSPCFG_SCI3_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/** MGCT: <category name="UART4 Settings"> */

/*
** Polled TTY device (UART4)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYD
    #define BSPCFG_ENABLE_TTYD              0
#endif

/*
** Interrupt-driven TTY device (UART4)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYD
    #define BSPCFG_ENABLE_ITTYD             0
#endif

/*
** TTYD and ITTYD baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI4_BAUD_RATE
    #define BSPCFG_SCI4_BAUD_RATE           115200
#endif

/*
** TTYD and ITTYD buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI4_QUEUE_SIZE
    #define BSPCFG_SCI4_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/** MGCT: <category name="UART5 Settings"> */

/*
** Polled TTY device (UART5)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYE
    #define BSPCFG_ENABLE_TTYE              0
#endif

/*
** Interrupt-driven TTY device (UART5)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYE
    #define BSPCFG_ENABLE_ITTYE             0
#endif

/*
** TTYE and ITTYE baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI5_BAUD_RATE
    #define BSPCFG_SCI5_BAUD_RATE           115200
#endif

/*
** TTYE and ITTYE buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI5_QUEUE_SIZE
    #define BSPCFG_SCI5_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/** MGCT: <category name="UART6 Settings"> */

/*
** Polled TTY device (UART6)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_TTYF
    #define BSPCFG_ENABLE_TTYF              0
#endif

/*
** Interrupt-driven TTY device (UART6)
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ITTYF
    #define BSPCFG_ENABLE_ITTYF             0
#endif

/*
** TTYF and ITTYF baud rate
** MGCT: <option type="number" min="0" max="115200"/>
*/
#ifndef BSPCFG_SCI6_BAUD_RATE
    #define BSPCFG_SCI6_BAUD_RATE           115200
#endif

/*
** TTYF and ITTYF buffer size
** MGCT: <option type="number" min="0" max="256"/>
*/
#ifndef BSPCFG_SCI6_QUEUE_SIZE
    #define BSPCFG_SCI6_QUEUE_SIZE          64
#endif

/** MGCT: </category> */

/*
** Polled I2C1 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_I2C1
    #define BSPCFG_ENABLE_I2C1              0
#endif

/*
** Interrupt-driven I2C1 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_II2C1
    #define BSPCFG_ENABLE_II2C1             0
#endif

/*
** Polled I2C2 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_I2C2
    #define BSPCFG_ENABLE_I2C2              0
#endif

/*
** Interrupt-driven I2C2 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_II2C2
    #define BSPCFG_ENABLE_II2C2             0
#endif

/*
** Polled I2C3 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_I2C3
    #define BSPCFG_ENABLE_I2C3              0
#endif

/*
** Interrupt-driven I2C3 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_II2C3
    #define BSPCFG_ENABLE_II2C3             0
#endif

/*
** Polled I2C4 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_I2C4
    #define BSPCFG_ENABLE_I2C4              0
#endif

/*
** Interrupt-driven I2C4 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_II2C4
    #define BSPCFG_ENABLE_II2C4             0
#endif

/*
** Enable SPI0 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_SPI0
    #define BSPCFG_ENABLE_SPI0              0
#endif

/*
** Enable SPI1 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_SPI1
    #define BSPCFG_ENABLE_SPI1              0
#endif

/*
** Enable SPI2 device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_SPI2
    #define BSPCFG_ENABLE_SPI2              0
#endif

/*
** RTC device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_RTCDEV
    #define BSPCFG_ENABLE_RTCDEV            0
#endif

/*
** ADC
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_ADC
    #define BSPCFG_ENABLE_ADC               0
#endif

/*
** IODEBUG device
** MGCT: <option type="bool"/>
*/
#ifndef BSPCFG_ENABLE_IODEBUG
    #define BSPCFG_ENABLE_IODEBUG           0
#endif

/** MGCT: </category> */

/*----------------------------------------------------------------------
**            MULTICORE SUPPORT
*/

/* IPC for Shared Memory */
// Set to let Shared memory driver that there is core specific support required
#define BSPCFG_IO_PCB_SHM_SUPPORT           1
#define BSPCFG_IO_PCB_SHM_RX_PRIO           2
#define BSPCFG_IO_PCB_SHM_TX_PRIO           2

/*----------------------------------------------------------------------
**                  DEFAULT MQX INITIALIZATION DEFINITIONS
** MGCT: <category name="Default MQX initialization parameters">
*/

/* Defined in link.xxx */
extern uint8_t       __ROM_END[];

extern uint8_t       __KERNEL_DATA_START[];
extern uint8_t       __KERNEL_DATA_END[];

extern uint8_t       __SHARED_RAM_START[];
extern uint8_t       __SHARED_RAM_END[];

extern uint8_t       __SHARED_CM_IRAM_START[];
extern uint8_t       __SHARED_CM_IRAM_END[];

extern uint8_t       __UNCACHED_DATA_START[];
extern uint8_t       __UNCACHED_DATA_END[];

extern uint8_t       __SRAM_POOL_START[];
extern uint8_t       __SRAM_POOL_END[];

#define BSP_DEFAULT_START_OF_KERNEL_MEMORY              ((void *)__KERNEL_DATA_START)
#define BSP_DEFAULT_END_OF_KERNEL_MEMORY                ((void *)__KERNEL_DATA_END)

#define BSP_DEFAULT_PROCESSOR_NUMBER                    ((uint32_t)1)

#ifndef MQX_AUX_CORE
#define MQX_AUX_CORE                                    0
#endif


#define BSP_SHARED_RAM_START                            ((void *)__SHARED_RAM_START)
#define BSP_SHARED_RAM_SIZE                             (__SHARED_RAM_END - __SHARED_RAM_START)

#if defined(__ARMCC_VERSION)
extern unsigned char Image$$SHARED_CM_IRAM_START$$Base[];
extern unsigned char Image$$SHARED_CM_IRAM_END$$Base[];
#define BSP_SHARED_IRAM_CM_START                        ((void *)Image$$SHARED_CM_IRAM_START$$Base)
#define BSP_SHARED_IRAM_CM_SIZE                         (Image$$SHARED_CM_IRAM_END$$Base - Image$$SHARED_CM_IRAM_START$$Base)
#else
#define BSP_SHARED_IRAM_CM_START                        ((void *)__SHARED_CM_IRAM_START)
#define BSP_SHARED_IRAM_CM_SIZE                         (__SHARED_CM_IRAM_END - __SHARED_CM_IRAM_START)
#endif

/*
** MGCT: <option type="string" quoted="false" allowempty="false"/>
*/
#ifndef BSP_DEFAULT_INTERRUPT_STACK_SIZE
    #define BSP_DEFAULT_INTERRUPT_STACK_SIZE            ((uint32_t)__DEFAULT_INTERRUPT_STACK_SIZE)
#endif

/* MGCT: <option type="list">
** <item name="1 (all levels disabled)" value="(1L)"/>
** <item name="2" value="(2L)"/>
** <item name="3" value="(3L)"/>
** <item name="4" value="(4L)"/>
** <item name="5" value="(5L)"/>
** <item name="6" value="(6L)"/>
** <item name="7" value="(7L)"/>
** </option>
*/
#ifndef BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX
    #define BSP_DEFAULT_MQX_HARDWARE_INTERRUPT_LEVEL_MAX      (2L)
#endif

/*
** MGCT: <option type="number"/>
*/
#ifndef BSP_DEFAULT_MAX_MSGPOOLS
    #define BSP_DEFAULT_MAX_MSGPOOLS                          (2L)
#endif

/*
** MGCT: <option type="number"/>
*/
#ifndef BSP_DEFAULT_MAX_MSGQS
    #define BSP_DEFAULT_MAX_MSGQS                             (16L)
#endif

/*
** Other Serial console options:(do not forget to enable BSPCFG_ENABLE_TTY define if changed)
**      "itty:"       interrupt mode
**      "ttya:"       uart0, polled mode
** MGCT: <option type="string" maxsize="256" quoted="false" allowempty="false"/>
 */
#ifndef BSP_DEFAULT_IO_CHANNEL
    #if BSPCFG_ENABLE_ITTYB
        #define BSP_DEFAULT_IO_CHANNEL                      "ittyb:"
        #define BSP_DEFAULT_IO_CHANNEL_DEFINED
    #else
        #define BSP_DEFAULT_IO_CHANNEL                        NULL
    #endif
#else
    /* undef is for backward compatibility with user_configh.h files which have already had it defined */
    #undef  BSP_DEFAULT_IO_CHANNEL_DEFINED
    #define BSP_DEFAULT_IO_CHANNEL_DEFINED
#endif

/*
** MGCT: <option type="string" maxsize="1024" quoted="false" allowempty="false"/>
*/
#ifndef BSP_DEFAULT_IO_OPEN_MODE
    #define BSP_DEFAULT_IO_OPEN_MODE                      (void *) (IO_SERIAL_XON_XOFF | IO_SERIAL_TRANSLATION | IO_SERIAL_ECHO)
#endif

/*
** FLASHX flash memory pool minimum size
** MGCT: <option type="string" maxsize="1024" quoted="false" allowempty="false"/>
*/
#if BSPCFG_ENABLE_FLASHX
    #ifndef BSPCFG_FLASHX_SIZE
        #define BSPCFG_FLASHX_SIZE      (FLASHX_END_ADDR - FLASHX_START_ADDR) /* defines maximum possible space */
    #endif
#else
    #undef  BSPCFG_FLASHX_SIZE
    #define BSPCFG_FLASHX_SIZE      0x0
#endif

/** MGCT: </category> */

#endif /* _imx6sx_sdb_m4_h_  */
