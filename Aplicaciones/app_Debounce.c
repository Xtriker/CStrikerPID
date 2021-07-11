/*
 * app_Debounce.c
 *
 *  Created on: 12 jun. 2020
 *      Author: Dario
 */
#include "app_Debounce.h"
#include "main.h"


/* El valor maximo tomado con el 5to display solo sera de 30000, por el cual no habra desbordamiento de los datos */
uint16_t TiempoPresionado = 0;
uint32_t Total = 0, Quinto = 0, Primero = 0, Segundo = 0, Tercero = 0, Cuarto = 0;
int8_t Aumento = 0u;
signed int Seleccion = 0;
uint8_t Seleccion_anterior[Numero_de_displays] = {0u,0u,0u,0u,0u}, Aumento_anterior[Numero_de_displays] = {0u,0u,0u,0u,0u};

/* Tiempo de activacion del Debounce por software */

enum{
	OpcionUno = 100,
	OpcionDos = 600
};

volatile uint8_t i= 0 ,a= 0;

/* Funcion que permite tener una doble funcion a los tres botones; la funcion primaria es activada cuando se realiza
 * una pulsacion sensilla de 100ms, eso realiza un aumento a la variable Seleccion para realizar el cambio de nuemros
 * en el display de 7 segmentos, miestras que la funcion avanzada, cuando se mantiene pulsado el boton a un tiempo
 * mayor de 600ms, se realiza el cambio del display de 7 segmentos.
 */
void app_Debounce(uint16_t Boton[], uint8_t Numero_Botones) {
	uint8_t Presionado[Numero_Botones];
	while (a < Numero_Botones + 1) {
		Presionado[a] = 0;
		a++;
	}

	while (HAL_GPIO_ReadPin(GPIOB, Boton[i]) == GPIO_PIN_RESET) {
		/* Se realiza una pausa de 500 ms */
		//delay_us(50000);
		/* Cambiando el valor del tiempo */
		delay_ms(30);
		TiempoPresionado = TiempoPresionado + 100;

		/* Guardando el valor del display actual en un array */
		Seleccion_anterior[Aumento] = Seleccion;
		Aumento_anterior[i] = Aumento;
		if (TiempoPresionado >= OpcionDos) {
			Presionado[i] = 0;
		} else {
			Presionado[i] = 1;
		}
	}

	if ((TiempoPresionado <= OpcionUno) && (Presionado[i] == 1)) {
		switch (i) {
		case 0: {
			TiempoPresionado = 0;

			Aumento = Numero_de_displays;
		}
			break;
		case 1: {
			TiempoPresionado = 0;
			Seleccion++;
		}
			break;
		case 2: {
			TiempoPresionado = 0;

			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			Seleccion--;

		}
			break;

		}
	}
	if ((TiempoPresionado >= OpcionDos) && (Presionado[i] == 0)) {
		switch (i) {
		case 0: {

			TiempoPresionado = 0;
			Aumento = 1;
		}
			break;
		case 1: {

			TiempoPresionado = 0;
			Aumento++;
			//HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
		}
			break;
		case 2: {
			TiempoPresionado = 0;
			if(Aumento == 0)
			{
				Aumento = 4;
			}
			else
			{
				Aumento--;
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			}
		}
			break;
		}
	} else {
		if (i >= Numero_Botones) {
			i = 0;
		} else {
			i++;
			a = 0;
		}
	}

}

void app_SeleccionarAngulo(void) {
	switch (Aumento) {
	case 0: {
		if (Seleccion > 3) {

			Primero = 0;
			Seleccion = 0;

		}
		if (Seleccion < 0) {

			Primero = 9;
			Seleccion = 9;

		} else {
			Primero = Seleccion * 10000;
			Total = Primero;
		}
	}
		break;
	case 1: {
		if (Seleccion > 8) {

			Segundo = 0;
			Seleccion = 0;

		}
		if (Seleccion < 0) {

			Segundo = 9;
			Seleccion = 9;

		} else {
			Segundo = Seleccion * 1000;
			Total = Segundo + Primero;
		}
	}
		break;
	case 2: {
		if (Seleccion > 9) {

			Tercero = 0;
			Seleccion = 0;
		}
		if (Seleccion < 0) {

			Tercero = 9;
			Seleccion = 9;
		} else {
			Tercero = Seleccion * 100;
			Total = Primero + Segundo + Tercero;
		}
	}
		break;
	case 3: {
		if (Seleccion > 9) {

			Cuarto = 0;
			Seleccion = 0;
		}
		if (Seleccion < 0) {

			Cuarto = 9;
			Seleccion = 9;
		} else {
			Cuarto = Seleccion * 10;
			Total = Primero + Segundo + Tercero + Cuarto;
		}
	}break;
	case 4: {
			if (Seleccion > 9) {

				Quinto = 0;
				Seleccion = 0;
			}
			if (Seleccion < 0) {

				Quinto = 9;
				Seleccion = 9;
			} else {
				Quinto = Seleccion;
				Total = Primero + Segundo + Tercero + Cuarto + Quinto;
			}
		}
		break;
	default: {

	}
	}
}


