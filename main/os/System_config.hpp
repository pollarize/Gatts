/*
 * System_config.hpp
 *
 *  Created on: Sep 17, 2017
 *      Author: Mihail Maldzhanski
 */

#ifndef MAIN_CONFIG_SYSTEM_CONFIG_HPP_
#define MAIN_CONFIG_SYSTEM_CONFIG_HPP_

//General pre-configuration of Arduino core general function naming
#define Os_Tasks_Init(void) app_main()

#define System_Loop_Stub(void) loop()

#define MCU_SOC_NAME        "ESP32"
#define MCU_FREQUENCY       ((uint32)80000000UL)

#endif /* MAIN_CONFIG_SYSTEM_CONFIG_HPP_ */
