#include <msp430.h>
#include "switches.h"
#include "led.h"

char switch_state_down, switch_state_changed; /* effectively boolean */
char songChoice = 0;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt sensitivity */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  switch_interrupt_handler();	/* to initially read the switches */
}

//determine the value of songChoice based on
//which button was pressed; songChoice will be
//used in songChooser(), which is declared in buzzer.c
//and has the interrupt handler call the appropriate
//method to play a melody
void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  if(!(p2val & SW1)){
    songChoice = 1;
   }
  if(!(p2val & SW2)){
    songChoice = 2;    
   }
  if(!(p2val & SW3)){
    songChoice = 3;
   }
  if(!(p2val & SW4)){
    songChoice = 4;
   }
   switch_state_changed = 1;
 
}
