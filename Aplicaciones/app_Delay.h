
#include "main.h"


#if defined(STM32L4)
	#include "stm32l412xx.h"
	#include "stm32l4xx_hal.h"
	#include "stm32l4xx_hal_gpio.h"
	#include "stm32l4xx_hal_tim.h"
#elif defined(STM32F1)
	#include "stm32f1xx.h"
	#include "stm32f1xx_hal.h"
	#include "stm32f1xx_hal_gpio.h"
	#include "stm32f1xx_hal_tim.h"
#endif


TIM_HandleTypeDef htim1;

extern void delay_us (uint16_t us);

extern void delay_ms (uint16_t ms);
