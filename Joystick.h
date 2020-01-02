#pragma once
class Joystick {
  public:
    Joystick(int xPin, int yPin, int switchPin, Stepper &stepperMotor);
    void debug();
    void manualControl();

  private:
    int _xPin; // analog pin connected to X output
    int _yPin; // analog pin connected to Y output
    int _switchPin; // digital pin connected to switch output
    Stepper& _motor;
};