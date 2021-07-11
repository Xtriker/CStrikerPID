#include "app_Delay.h"

void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
}


void delay_ms (uint16_t ms)
{
	uint32_t conversion = 0;
	__HAL_TIM_SET_COUNTER(&htim1,0);
	conversion = ms * 1000;
	while (__HAL_TIM_GET_COUNTER(&htim1) < conversion);
}
