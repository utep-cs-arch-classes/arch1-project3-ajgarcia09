#Music Toy on MSP430

This directory contains necessary code to play three songs on the MSP430:

    *1. Twinkle, Twinkle Little Star (S2)
    *2. Brahm's Lullaby (S3)
    *3. When the Saints Come Marching In (S4)

The red and green LEDs toggle back and forth to the music tempo while each song is playing.

To test it out, make sure your MSP430 is recognized by your device, and the expansion board (P2) is connected to the pins on Port 1. To compile the code, within the project directory try:

*$ make

Within the musicToy directory try:

*$ make load

You will see the green and red LEDs toggling back and forth.

*To play Twinkle Twinkle little Star press the button labeled with S2 on the expansion board.

*To play Brahm's Lullaby press the button labeled with S3.

*To play When the Saints Come Marching In press the button labeled with S4.

*To pause the music, press the button labeled with S1.

*To resume playing the paused song, press the corresponding button to the song (If you paused Lullaby by pressing S1, press S2 and Lullaby will resume playing). Otherwise, press any other button if you'd like to play another song.

I developed this program by editing code found in

*project2-blinkytoy-ajgarcia09/demos

I received help from Abner Palomino in designing the arrays that hold the note sequences for each song. Also, I had a bug that only allowed me to play the first note of each song when I pressed the corresponding button, instead of playing the entire melody. Armando Hernandez helped me find and fix this bug.