/*
 * HW_config.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: Mihail Maldzhanski
 */

#ifndef MAIN_CONFIG_HW_CONFIG_HPP_
#define MAIN_CONFIG_HW_CONFIG_HPP_

//HW Abstraction definitions

//----------------------------------------------------------------------------
//Required Interfaces
//----------------------------------------------------------------------------
#define RI_AnalogRead(pin)                     analogRead(pin)
#define RI_DigitalRead(pin)                    digitalRead(pin)
#define RI_AnalogWrite(pin,value)              analogWrite(pin,value)
#define RI_DigitalWrite(pin,value)             digitalWrite(pin,value)
#define RI_SetPinAsInput(pin)                  pinMode((pin),INPUT_PULLUP)
#define RI_SetPinAsOutput(pin)                 pinMode((pin),OUTPUT)

//----------------------------------------------------------------------------
//OUTPUTS
//----------------------------------------------------------------------------
#ifndef HWA_DO_HEATER
#define HWA_DO_HEATER ((uint8_t)9)
#endif

#ifndef HWA_DO_PUSHER
#define HWA_DO_PUSHER ((uint8_t)10)
#endif

#ifndef HWA_DO_BUZZER
#define HWA_DO_BUZZER ((uint8_t)5)
#endif

#ifndef HWA_PWM_FAN
#define HWA_PWM_FAN ((uint8_t)11)
#endif

#ifndef HWA_PWM_LCD_BACKLIGHT
#define HWA_PWM_LCD_BACKLIGHT ((uint8_t)3)
#endif

//----------------------------------------------------------------------------
//INPUTS
//----------------------------------------------------------------------------
#ifndef HWA_AI_BUTTONS_SET
#define HWA_AI_BUTTONS_SET A0
#endif

#ifndef HWA_AI_BUTTONS_SET_COUNT
#define HWA_AI_BUTTONS_SET_COUNT 4
#endif

#ifndef HWA_AI_SAFETY_HEATER
#define HWA_AI_SAFETY_HEATER A1
#endif

#ifndef HWA_AI_SAFETY_PUSHER
#define HWA_AI_SAFETY_PUSHER A2
#endif

#ifndef HWA_AI_SAFETY_FAN
#define HWA_AI_SAFETY_FAN A3
#endif

#ifndef HWA_AI_SAFETY_LCD_BACKLIGHT
#define HWA_AI_SAFETY_LCD_BACKLIGHT A7
#endif

#ifndef HWA_DI_BUTTON_ENTER
#define HWA_DI_BUTTON_ENTER ((uint8_t)4)
#endif

//----------------------------------------------------------------------------
//PROTOCOLS
//----------------------------------------------------------------------------
#ifndef HWA_I2C_SDA
#define HWA_I2C_SDA A4
#endif

#ifndef HWA_I2C_SCL
#define HWA_I2C_SCL A5
#endif

#ifndef HWA_SPI_TC_SO
#define HWA_SPI_TC_SO ((uint8_t)8)
#endif

#ifndef HWA_SPI_TC_SC
#define HWA_SPI_TC_SC ((uint8_t)7)
#endif

#ifndef HWA_SPI_TC_CLK
#define HWA_SPI_TC_CLK ((uint8_t)6)
#endif

#endif /* MAIN_CONFIG_HW_CONFIG_HPP_ */
