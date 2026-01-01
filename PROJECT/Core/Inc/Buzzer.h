/*
 * Buzzer.h
 *
 *  Created on: Dec 30, 2025
 *      Author: hp
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>

extern volatile uint16_t value;
extern ADC_HandleTypeDef hadc1;
uint16_t adc_conversion(void);
void gas_buzzer(void);

#endif /* INC_MQ2_H_ */
