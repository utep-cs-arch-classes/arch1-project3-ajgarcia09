This directory contains necessary code to play three songs on the MSP430:

     1. Twinkle, Twinkle Little Star
     2. Brahm's Lullaby
     3. When the Saints Come Marching In

The red and green LEDs toggle back and forth while each song is playing.

To test it out, make sure your MSP430 is recognized by your device. Then, within the project directory try:

$ make

Within the musicToy directory try:

$ make load

To test out the different songs, within bbmain.c uncomment the song you want to listen to and make sure the rest are commented. Do the same in the interruptWDT() ini the wdInterruptHandler.c file. Make sure you are only testing out one song at a time.