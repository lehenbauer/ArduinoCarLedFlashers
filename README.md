# source code and stuff to run car LED lights

## carQuadLedFlasher.ino

Defines four DIO output pins, UPPER_LEFT_LED, LOWER_LEFT_LED, UPPER_RIGHT_LED, LOWER_RIGHT_LED.

Presumes upper and lower are standalone pairs.  Lower is for instance yellow LED light arrays and upper are LED fog lights.

The pushbutton cycles through a state machine of the following sequences
* all off
* fog lights on solid
* lower lights on solid
* all lights on solid
* all four lights safety blinking pattern
* fog lights on, lower lights safety blinking pattern

The program compiles to about 2K of flash and uses at most tens of bytes of RAM.

[[https://raw.githubusercontent.com/lehenbauer/ArduinoCarLedFlashers/master/images/breadboard-photo.jpg]]
