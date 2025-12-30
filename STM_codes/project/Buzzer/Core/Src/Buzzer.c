/*
 * Buzzer.c
 *
 *  Created on: Dec 30, 2025
 *      Author: hp
 */


/*
 * mq2.c
 *
 *  Created on: Dec 30, 2025
 *      Author: Hp
 */
#include "main.h"   // ðŸ‘ˆ VERY IMPORTANT
#include "buzzer.h"
#include "my_lcd.h"

  // <-- actual definition


/* Standard C libraries */
#include <stdio.h>      // for
#include <string.h>     // for string handling
#include <stdarg.h>     // for variable arguments

/* STM32 HAL library */
#include "stm32f4xx_hal.h"
uint16_t adc_conversion(void)
{
    uint16_t value;
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return value;
}

/*void print_putty(void)
{
	sprintf(str1, "MQ2 Gas Value: %d\r\n", val);
	HAL_UART_Transmit(&huart2, (uint8_t*)str1, strlen(str1), HAL_MAX_DELAY);
}*/
void gas_buzzer(void)
{

				  //sprintf(str2, "GAS DETECTED!!!\r\n");
				  //HAL_UART_Transmit(&huart2, (uint8_t*)str2, strlen(str2), HAL_MAX_DELAY);
				lcd16x2_i2c_printf("GAS DETECTED!!!");
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

}

