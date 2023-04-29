
#ifndef __RCC_H

#include <stdint.h>

#define CLKPR_REG *(volatile uint8_t *)0x61  /*clock prescaler register*/

void clock_config();
void delay_ms(double delay_counter);

#endif