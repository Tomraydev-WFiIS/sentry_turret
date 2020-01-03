#include "Stepper.h"
#include "config.h"
#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, int switchPin, Stepper& stepperMotor)
  : _xPin(xPin), _yPin(yPin), _switchPin(switchPin), _motor(stepperMotor){
  pinMode(_switchPin, INPUT);
  digitalWrite(_switchPin, HIGH); // enable the internal pullup on the input pin
}

void Joystick::debug(){
  String msg = "Switch: " + String(digitalRead(_switchPin));
  msg += "\tX-axis: " + String(analogRead(_xPin));
  msg += "\tstep_number: " + String(_motor.step_number);
  Serial.println("debug," + msg);
}

void Joystick::manualControl(){
  Serial.println("debug,Entering manual control mode.");
  delay(3000);
  int x = 512; // zero state
  while (true){
    this->debug();
    x = analogRead(_xPin);
    if(x > 700){
      _motor.step(6);
    } else if (x < 300){
      _motor.step(-6);
    }
    if(!digitalRead(_switchPin)){
      Serial.println("debug,Entering automatic control mode.");
      delay(1000);
      return;
    }
  }
}