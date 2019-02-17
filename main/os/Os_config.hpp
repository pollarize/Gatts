/*
 * Os_config.hpp
 *
 *  Created on: Sep 17, 2017
 *      Author: Mihail Maldzhanski
 */

#ifndef MAIN_CONFIG_OS_CONFIG_HPP_
#define MAIN_CONFIG_OS_CONFIG_HPP_

//-----------------------------------------------------------------------------------------
//General Includes
//-----------------------------------------------------------------------------------------
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"

//-----------------------------------------------------------------------------------------
//General Defines
//-----------------------------------------------------------------------------------------
//Task Times
#define OS_TASK_MIN_TIME ((uint16_t)15)       //in ms
#define OS_TASK_AVG_TIME ((uint16_t)45)       //in ms
#define OS_TASK_MAX_TIME ((uint16_t)105)      //in ms
#define OS_TASK_EXTENDED_TIME ((uint16_t)990) //in ms

//Task Stack Sizes
#define OS_STACK_SIZE_KBYTES ((uint32_t)10 * 1024)
#define OS_TASK_MIN_WORDS ((uint16_t)OS_STACK_SIZE_KBYTES)                              //in bytes count
#define OS_TASK_AVG_WORDS ((uint16_t)OS_STACK_SIZE_KBYTES + (OS_STACK_SIZE_KBYTES / 2)) //in bytes count
#define OS_TASK_MAX_WORDS ((uint16_t)OS_TASK_MIN_WORDS * 2)                             //in bytes count

//Task Priorities
#define OS_TASK_PRIORITY_HIGH ((uint8_t)1)
#define OS_TASK_PRIORITY_MEDIUM ((uint8_t)2)
#define OS_TASK_PRIORITY_LOW ((uint8_t)3)

#if configUSE_PREEMPTION != true
#undef configUSE_PREEMPTION
#define configUSE_PREEMPTION false
#endif

//-----------------------------------------------------------------------------------------
//General Types
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Static Data
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Exported Data
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Static Function Prototypes
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Exported Function Prototypes
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Static Functions
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Exported Functions
//-----------------------------------------------------------------------------------------

#endif /* MAIN_CONFIG_OS_CONFIG_HPP_ */
