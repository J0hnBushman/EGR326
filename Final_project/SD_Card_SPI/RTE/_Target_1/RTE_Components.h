
/*
 * Auto generated Run-Time-Environment Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'SD_read' 
 * Target:  'Target 1' 
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File: 
 */
#define CMSIS_device_header "stm32f4xx.h"

/* ARM::CMSIS:RTOS:Keil RTX:4.82.0 */
#define RTE_CMSIS_RTOS                  /* CMSIS-RTOS */
        #define RTE_CMSIS_RTOS_RTX              /* CMSIS-RTOS Keil RTX */
/* Keil.ARM Compiler::Compiler:Event Recorder:DAP:1.5.1 */
#define RTE_Compiler_EventRecorder
          #define RTE_Compiler_EventRecorder_DAP
/* Keil.ARM Compiler::Compiler:I/O:File:File System:1.2.0 */
#define RTE_Compiler_IO_File            /* Compiler I/O: File */
          #define RTE_Compiler_IO_File_FS         /* Compiler I/O: File (File System) */
/* Keil.ARM Compiler::Compiler:I/O:STDERR:ITM:1.2.0 */
#define RTE_Compiler_IO_STDERR          /* Compiler I/O: STDERR */
          #define RTE_Compiler_IO_STDERR_ITM      /* Compiler I/O: STDERR ITM */
/* Keil.ARM Compiler::Compiler:I/O:STDIN:ITM:1.2.0 */
#define RTE_Compiler_IO_STDIN           /* Compiler I/O: STDIN */
          #define RTE_Compiler_IO_STDIN_ITM       /* Compiler I/O: STDIN ITM */
/* Keil.ARM Compiler::Compiler:I/O:STDOUT:ITM:1.2.0 */
#define RTE_Compiler_IO_STDOUT          /* Compiler I/O: STDOUT */
          #define RTE_Compiler_IO_STDOUT_ITM      /* Compiler I/O: STDOUT ITM */
/* Keil.MDK-Plus::File System:CORE:LFN Debug:6.15.3 */
#define RTE_FileSystem_Core             /* File System Core */
          #define RTE_FileSystem_LFN              /* File System with Long Filename support */
          #define RTE_FileSystem_Debug            /* File System Debug Version */
/* Keil.MDK-Plus::File System:Drive:Memory Card:6.15.3 */
#define RTE_FileSystem_Drive_MC_0       /* File System Memory Card Drive 0 */

/* Keil::CMSIS Driver:SPI:2.18 */
#define RTE_Drivers_SPI1                /* Driver SPI1 */
        #define RTE_Drivers_SPI2                /* Driver SPI2 */
        #define RTE_Drivers_SPI3                /* Driver SPI3 */
        #define RTE_Drivers_SPI4                /* Driver SPI4 */
        #define RTE_Drivers_SPI5                /* Driver SPI5 */
        #define RTE_Drivers_SPI6                /* Driver SPI6 */
/* Keil::Device:STM32Cube Framework:Classic:1.8.1 */
#define RTE_DEVICE_FRAMEWORK_CLASSIC
/* Keil::Device:STM32Cube HAL:Common:1.8.1 */
#define RTE_DEVICE_HAL_COMMON
/* Keil::Device:STM32Cube HAL:Cortex:1.8.1 */
#define RTE_DEVICE_HAL_CORTEX
/* Keil::Device:STM32Cube HAL:DMA:1.8.1 */
#define RTE_DEVICE_HAL_DMA
/* Keil::Device:STM32Cube HAL:GPIO:1.8.1 */
#define RTE_DEVICE_HAL_GPIO
/* Keil::Device:STM32Cube HAL:PWR:1.8.1 */
#define RTE_DEVICE_HAL_PWR
/* Keil::Device:STM32Cube HAL:RCC:1.8.1 */
#define RTE_DEVICE_HAL_RCC
/* Keil::Device:STM32Cube HAL:SPI:1.8.1 */
#define RTE_DEVICE_HAL_SPI
/* Keil::Device:Startup:2.6.3 */
#define RTE_DEVICE_STARTUP_STM32F4XX    /* Device Startup for STM32F4 */


#endif /* RTE_COMPONENTS_H */