#include <msp430.h>
#include "led.h"

unsigned char led_state = 0;
unsigned char count = 0;
unsigned char led_changed = 0;

void led_init()
{
  P1DIR |= LEDS;		// bits attached to leds are output
  led_changed = 1;
  led_update();
}

void led_update()
{
  if (led_changed) {
    char ledFlags = 0;
    if(led_state){
      ledFlags |= LED_GREEN;
    }
    else{
      ledFlags |= LED_RED;
    }
    P1OUT &= (0xff^LEDS) | ledFlags; // clear bit for off leds
    P1OUT |= ledFlags;		     // set bit for on leds
    led_changed = 0;
  }
}

void led_toggle() {
  led_state = 1 - led_state;
  led_changed = 1;
}
