
#include "RCC.h"

/*
*  16MHz clock is used 
*  1/16 = 0.625 / 1000000 -> 1 ticks
*  x ticks ms- > 0.625 * x * delay_counter/1000;
*/
void delay_ms(double delay_counter)      
{
  delay_counter = (0.0625 * 1000 * delay_counter);
  while(delay_counter--);
}

void clock_config()
{
  //16MHZ ideal clock is used , no prescaler used
  CLKPR_REG &= 0x80; 

}