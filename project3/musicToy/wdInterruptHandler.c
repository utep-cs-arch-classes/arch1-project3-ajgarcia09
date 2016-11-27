#include <msp430.h>
#include "buzzer.h"
#include "led.h"


__interrupt(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char count = 0;

  if(++count == 70){
    songChooser();
    count=0;
   }
  led_update();
}
