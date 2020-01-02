#ifndef config_h
#define config_h

#include "Arduino.h"
#define STEPS 2038 // the number of steps in one revolution of your motor (28BYJ-48)

// Joystick
const int switchPin = 2;
const int xPin = A0;
const int yin = A1;

// Ultrasonic sensor
const int trigPin = 5;
const int echoPin = 6;

// Other
const int minStep = 6;

#endif