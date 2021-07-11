/*
 * app_DigitalDimmer.h
 *
 *  Created on: 9 jul. 2020
 *      Author: dario
 */

#ifndef APP_DIGITALDIMMER_H_
#define APP_DIGITALDIMMER_H_

#define true uint8_t(1u)
#define false uint8_t(0u)

#include "main.h"
#include "pid_controller.h"
#include "app_Delay.h"
#include "app_MAX7219.h"
#include "app_Debounce.h"
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

enum{
	  Debounce,
	  Inicio,
	  Ecuacion,
	  Dimmer,
	  PID
  }opcion;

extern void app_Dimmer(void);
extern void app_PIDDimmer(uint16_t Frecuencia);
extern void app_Dimmer_Prueba(void);

#endif /* APP_DIGITALDIMMER_H_ */
