#ifndef INC_MQ2_H_
#define INC_MQ2_H_

#include <stdint.h>

extern volatile uint16_t value;

uint16_t adc_conversion(void);
void gas_led(void);

#endif /* INC_MQ2_H_ */
