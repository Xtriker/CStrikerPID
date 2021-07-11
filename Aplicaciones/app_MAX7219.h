/*
 * app_MAX7219.h
 *
 *  Created on: Jul 22, 2020
 *      Author: dario
 */

#ifndef APP_MAX7219_H_
#define APP_MAX7219_H_


#include "main.h"
#include "app_Delay.h"


#if defined(STM32L4)
	#include "stm32l412xx.h"
	#include "stm32l4xx_hal.h"
	#include "stm32l4xx_hal_spi.h"
	#include "stm32l4xx_hal_gpio.h"
#elif defined(STM32F1)
	#include "stm32f1xx.h"
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_spi.h"
	#include "stm32f1xx_hal_gpio.h"
#endif

SPI_HandleTypeDef hspi1;

#define DECODE_MODE       	 0x09
#define INTENSITY    		 0x0A
#define SCAN_LIMIT   	 	 0x0B
#define SHUTDOWN        	 0x0C
#define DISPLAY_TEST    	 0x0F
#define DISABLE_DECODE       0x00
#define DECODE_ALL			 0xFF
#define BRIGHTNESS			 0x0D
#define SCAN_LOW_NIBBLE		 0x03
#define SCAN_ALL_DIGITS		 0x07
#define SHUTDOWN_MODE		 0x00
#define NORMAL_OPERATION     0x01
#define	DISABLE_TEST_MODE	 0x00
#define ENABLE_TEST_MODE	 0x01

extern void app_InitMAX7219(void);
extern void app_TestMX7219(void);

extern void app_NumeroAMAX7219(uint32_t Numero, uint8_t Numero_displays);
//extern void FloatAMAX7912(float Numero, uint8_t Numero_display);
extern void app_ApagarDisplay(void);
extern void app_EncenderDisplay(void);
extern void app_BrilloDisplay(uint8_t Brillo);
extern void app_LimpiarDisplays(void);
extern void app_LimpiarDisplay(uint8_t Display);

extern void SPI_CS_ENABLE(void);
extern void SPI_CS_DISABLE(void);
extern void SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t data);

#endif /* APP_MAX7219_H_ */
