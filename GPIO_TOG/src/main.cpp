#include <stdint.h>
#include "GPIO.h"
#include "RCC.h"

int main()
{
  clock_config();
  pin_dir(PORTB , PB5);

  while(1)
  {
    pin_tog(PORTB , PB5);
    delay_ms(500);
  }

}