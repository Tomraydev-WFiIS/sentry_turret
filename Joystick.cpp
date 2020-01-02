#include "Stepper.h"
#include "config.h"
#include "Joystick.h"

Joystick::Joystick(int xPin, int yPin, int switchPin, Stepper& stepperMotor)
  : _xPin(xPin), _yPin(yPin), _switchPin(switchPin), _motor(stepperMotor){
  pinMode(_switchPin, INPUT);
  digitalWrite(_switchPin, HIGH); // enable the internal pullup on the input pin
}

void Joystick::debug(){
  Serial.print("Switch:  ");
  Serial.print(digitalRead(_switchPin));
  Serial.print("\tX-axis: ");
  Serial.print(analogRead(_xPin));
  Serial.print("\tstep_number: ");
  Serial.print(_motor.step_number);
  Serial.print("\n");
}

void Joystick::manualControl(){
  Serial.println("Entering manual control mode.");
  delay(1000);
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
      Serial.println("Entering automatic control mode.");
      delay(1000);
      return;
    }
  }
}