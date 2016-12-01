##Project 3

shapemotion.c creates a snowman and falling snow using elements from the libShape directory.

Each shape is created using a Layer struct (found in shape.h).

Movable layers are stored in a linked list of struct type MovLayer (defined in shapemotion.c).

I modified the method mlAdvance() found in the original code and renamed it letItSnow(). mlAdvance() made movable layers bounce off the margins of a "fence" boundary. Instead, letItSnow() allows the shapes to move from the top of the screen and once they reach the bottom, the shapes are redrawn at the top of the screen. This simulates falling snow.

To test it out make sure your MSP430 is connected and recognized by your device.

In the arch1-project3-ajgarcia09 directory type

$ make

In shape-motion-demo directory type

$ make load

To rest the screen and all components, either make load again from shape-motion-demo or press the RESET button on the MSP430.

