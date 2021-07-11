/*
 * app_MAX7219.c
 *
 *  Created on: Jul 22, 2020
 *      Author: dario
 */

#include "app_MAX7219.h"

/*  ----------------------------
 * | Pin |  Label     | MAX pin |
 * | PA5 |	SPI1_SCK  |	CLK     |
 * | PA6 |	SP1_MISO  | NC      |
 * | PA7 |	SPI1_MOSI |	DIN     |
 * | PA4 | SOFT SLAVE |	CSS     |
 *  ----------------------------
 */

void SPI_CS_ENABLE(void)
{
	do{
		HAL_GPIO_WritePin(CSS_GPIO_Port, CSS_Pin, GPIO_PIN_RESET);
	}while(0);
}

void SPI_CS_DISABLE(void)
{
	do{
		HAL_GPIO_WritePin(CSS_GPIO_Port, CSS_Pin, GPIO_PIN_SET);
	}while(0);
}
void SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t data) {
    // 2nd parameter - pData: pointer to data buffer
    HAL_SPI_Transmit(hspi, (uint8_t *) &data, 1, 1000);
}

void app_InitMAX7219(void)
{
    SPI_CS_ENABLE();
    SPI_Transmit(&hspi1, DECODE_MODE);
    SPI_Transmit(&hspi1, 0xff);
    SPI_CS_DISABLE();

    SPI_CS_ENABLE();
    SPI_Transmit(&hspi1, INTENSITY);
    SPI_Transmit(&hspi1, BRIGHTNESS); 	/* Selecciona el nivel de brillo del display de 7 segmentos */
    SPI_CS_DISABLE();

    SPI_CS_ENABLE();
    SPI_Transmit(&hspi1, SCAN_LIMIT);
    SPI_Transmit(&hspi1, 0x05);
    SPI_CS_DISABLE();

    SPI_CS_ENABLE();
    SPI_Transmit(&hspi1, SHUTDOWN);
    SPI_Transmit(&hspi1, NORMAL_OPERATION);
    SPI_CS_DISABLE();

    SPI_CS_ENABLE();
	SPI_Transmit(&hspi1, DISPLAY_TEST);
	SPI_Transmit(&hspi1, ENABLE_TEST_MODE);
	SPI_CS_DISABLE();

	SPI_CS_ENABLE();
	SPI_Transmit(&hspi1, DISPLAY_TEST);
	SPI_Transmit(&hspi1, DISABLE_TEST_MODE);
	SPI_CS_DISABLE();
}

void app_NumeroAMAX7219(uint32_t Numero, uint8_t Numero_displays)
{
	  volatile uint8_t i;
	  for(i = Numero_displays ;(Numero > 0) || (Numero_displays - i >= 0) ; Numero/=10,i--)
	  {
		SPI_CS_ENABLE();
		SPI_Transmit(&hspi1,i);
	    SPI_Transmit(&hspi1,Numero%10);
	    SPI_CS_DISABLE();
	  }
}

void app_ApagarDisplay(void)
{
	SPI_CS_ENABLE();
	SPI_Transmit(&hspi1, SHUTDOWN);
	SPI_Transmit(&hspi1, DISABLE_DECODE);
	SPI_CS_DISABLE();
}

void app_EncenderDisplay(void)
{
	SPI_CS_ENABLE();
	SPI_Transmit(&hspi1, SHUTDOWN);
	SPI_Transmit(&hspi1, NORMAL_OPERATION);
	SPI_CS_DISABLE();
}

void app_BrilloDisplay(uint8_t Brillo)
{
	if((Brillo >= 0) && (Brillo <= 15))
	  {
	    SPI_CS_ENABLE();
	    SPI_Transmit(&hspi1, 0x0A);
	    SPI_Transmit(&hspi1, Brillo);
	    SPI_CS_DISABLE();
	  }
}
void app_LimpiarDisplays(void)
{
	for(uint8_t i = 1; i < 6;i++)
	{
	SPI_CS_ENABLE();
	SPI_Transmit(&hspi1,i);
	SPI_Transmit(&hspi1,0x00);
	SPI_CS_DISABLE();
	}
}

void app_LimpiarDisplay(uint8_t Display)
{
		SPI_CS_ENABLE();
		SPI_Transmit(&hspi1,Display);
		SPI_Transmit(&hspi1,0xF);
		SPI_CS_DISABLE();
}
/* Contador de 0 a 99999 en 5 displays de 7 segmentos */
void app_TestMX7219(void)
{
	uint16_t i;
	for(i=0;i<99999;i++)
	{
	  app_NumeroAMAX7219(i,5);
	  delay_ms(100);
	}
}
