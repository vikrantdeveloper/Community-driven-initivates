
#ifndef __GPIO_H
#include <stdint.h>

#define DDR_PORTB *(volatile uint8_t *)0x24  /*direction register*/   /*-> PORT1 -> PORTB*/
#define OP_PORTB  *(volatile uint8_t *)0x25  /*I/P output register*/

typedef enum{
    PORTB = 1,
    PORTC = 2,
    PORTD = 3
}port_en;

#define PB0   0
#define PB1   1
#define PB2   2 
#define PB3   3
#define PB4   4
#define PB5   5
#define PB6   6
#define PB7   7

#define HIGH   1
#define LOW    0

/*
*      API
*/

void pin_dir(port_en port_en_val , uint8_t pin);
void pin_tog(port_en port_en_val , uint8_t pin);

#endif