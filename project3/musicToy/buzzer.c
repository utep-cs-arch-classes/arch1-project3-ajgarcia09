#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

#define MIN_PERIOD 1000
#define MAX_PERIOD 4000

/*Each array has a sequence of notes that play the given song. A "0" means a space in between each note. Sequences of the same note mean the note has a longer duration (E4,E4 would last twice as long as E4)*/

int twinkle[] = {C4,0,C4,0,G4,0,G4,0,A4,0,A4,0,G4,G4,0,0,F4,0,F4,0,E4,0,E4,0,D4,0,D4,0,C4,C4,0,-1};

int lullaby[]={E4,0,E4,0,G4,G4,0,E4,0,E4,0,G4,G4,0,E4,0,E4,0,C5,0,B4,0,A4,0,A4,0,G4,0,D4,0,E4,0,F4,0,D4,0,D4,0,E4,0,F4,F4,0,D4,0,F4,0,B4,0,A4,0,G4,0,B4,0,C5,-1};

int saints[]={C4,0,E4,0,F4,0,G4,G4,G4,G4,0,C4,0,E4,0,F4,0,G4,G4,G4,G4,0,C4,0,E4,0,F4,0,G4,0,E4,0,C4,0,E4,0,D4,D4,D4,D4,0,E4,0,E4,0,D4,D4,0,C4,0,C4,0,E4,0,G4,0,G4,0,F4,F4,F4,F4,0,C4,0,E4,0,F4,0,G4,0,E4,0,C4,0,D4,0,C4,C4,C4,C4,-1};

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */
}

void playTwinkle(){
  static int i =-1;
    i++;
    if(twinkle[i]==-1)
      i=0;
    buzzer_set_period(twinkle[i]);	//play Twinkle Twinkle Little Star
    led_toggle(); 
}

void playLullaby(){
  static int a =-1;
    a++;
    if(lullaby[a]==-1)
      a=0;
    buzzer_set_period(lullaby[a]);	//play Brahm's Lullaby
    led_toggle();
}

void playSaints(){
   static int b =-1;
    b++;
    if(saints[b]==-1)
      b=0;
    buzzer_set_period(saints[b]); //Play When the Saints Come Marching In
    led_toggle();
}

void buzzer_set_period(short cycles)
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		//one half cycle
}

//determine which song to play based on songChoice,
//whose value will be set by the user pressing different buttons
void songChooser(){
  switch(songChoice){
  case 1://button SW1
    buzzer_set_period(0); //pause song that's playing
     break;
  case 2://button SW2
    playTwinkle();
    break;
  case 3://button SW3
    playLullaby();
    break;
  case 4://button SW4
    playSaints();
    break;
  default:
    led_toggle();
  }
}
