

#include "GPIO.h"

void pin_dir(port_en port_en_val , uint8_t pin)
{
  if(port_en_val == PORTB)
    DDR_PORTB |= (1 << pin); 
}
void pin_tog(port_en port_en_val , uint8_t pin)
{
  if(port_en_val == PORTB)
    OP_PORTB ^= (1 << pin);
}