#include <msp430.h>
#include "switches.h"
#include "buzzer.h"

#define MIN_PERIOD 1000
#define MAX_PERIOD 4000

/*Each array has a sequence of notes that play the given song. A "0" means a space in between each note. Sequences of the same note mean the note has a longer duration (E4,E4 would last twice as long as E4)*/

int joy[] = {C5,C5,0,B4,0,A4,0,G4,G4,F4,0,E4,E4,0,D4,D4,0,D4,D4,0,G4,0,A4,A4,A4,0,A4,0,B4,B4,0,B4,0,C5,C5,C5,C5,-1};
  
int frosty[]={G4,G4,0,E4,0,F4,0,G4,0,C5,C5,B4,0,C5,0,D5,0,C5,B4,0,A4,0,G4,G4,0,B4,0,C5,0,D5,0,C5,0,B4,0,A4,0,A4,0,G4,0,C5,0,E4,0,G4,A4,0,G4,F4,E4,0,F4,G4,G4,G4,G4,-1};

int babyItsCold[]={C4,0,A4,0,G4,0,F4,0,C5,0,C5,C5,0,C4,0,A4,0,G4,0,F4,0,A4,0,A4,0,F4,0,F4,0,F4,0,C4,0,Bb4,0,A4,0,G4,0,C5,0,C5,C5,0,C4,0,Bb4,0,A4,0,G4,0,Bb4,0,B4,0,G4,0,G4,0,G4,0,F4,0,G4,0,A4,0,B4,0,Bb4,0,F4,F4,0,F4,-1};

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

void playJoy(){
  static int i =-1;
    i++;
    if(joy[i]==-1)
      i=0;
    buzzer_set_period(joy[i]);//play Twinkle Twinkle Little Star
    led_toggle(); 
}

void playFrosty(){
  static int a =-1;
    a++;
    if(frosty[a]==-1)
      a=0;
    buzzer_set_period(frosty[a]);	//play Brahm's Lullaby
    led_toggle();
}

void playBabyItsCold(){
   static int b =-1;
    b++;
    if(babyItsCold[b]==-1)
      b=0;
    buzzer_set_period(babyItsCold[b]); //Play When the Saints Come Marching In
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
    playJoy();
    break;
  case 3://button SW3
    playFrosty();
    break;
  case 4://button SW4
    playBabyItsCold();
    break;
  default:
    led_toggle();
  }
}
