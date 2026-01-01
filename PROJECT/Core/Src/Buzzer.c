/*
 * Buzzer.c
 *
 *  Created on: Dec 30, 2025
 *      Author: hp
 */

#include "main.h"
#include "buzzer.h"
#include "my_lcd.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "Buzzer.h"

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


void gas_buzzer(void)
{

				lcd16x2_i2c_printf("GAS DETECTED!!!");
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
				HAL_Delay(1000);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);

}

