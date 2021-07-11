/*
 * app_Debounce.h
 *
 *  Created on: 12 jun. 2020
 *      Author: Dario
 */


/* Librerias usadas para el programa */


#include <stdio.h>

#include "app_Delay.h"
#include "app_MAX7219.h"

#define Numero_de_displays 5

/* Seleccion del microcontrolador
 * si no se encuentra el microcontrolador
 * colcar el suyo en la lista de abajo
 */
#if defined(STM32L4)
	#include "stm32l412xx.h"
	#include "stm32l4xx_hal.h"
	#include "stm32l4xx_hal_gpio.h"
#elif defined(STM32F1)
	#include "stm32f1xx.h"
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_gpio.h"
#endif

extern void app_Debounce(uint16_t Boton[], uint8_t Numero_Botones);
extern void app_SeleccionarAngulo(void);
extern uint32_t Total;
extern int8_t Aumento;

