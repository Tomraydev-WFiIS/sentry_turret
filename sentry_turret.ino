#include "Stepper.h"
#include "Joystick.h"
#include "config.h"

// Motor
Stepper stepper(STEPS, 8, 10, 9, 11);

// Joystick
Joystick joystick(A0, A1, switchPin, stepper);

// ******** Functions ********
int angleToStep(double a){
  return a/360.0*STEPS;
}

double stepToAngle(int s){
  return double(s)/double(STEPS) * 360.0;
}

int sgn(int val){
  return (0 < val) - (val < 0);
}

void stepAndScan(int steps){
  double distance;
  double angle;
  steps = steps - steps % minStep;
  for(int i = 0; i < abs(steps); i += minStep){
    stepper.step(sgn(steps)*minStep);
    distance = ping();
    angle = stepToAngle(stepper.step_number);
    Serial.println("data," + String(angle) + "," + String(distance));
  }
}

void observe(double angleOfView){
  int range = angleToStep(angleOfView)/2.0;
  
  // move half left
  stepAndScan(range);
  //  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number); // debug
  delay(100);
  
  
  // move full right
  stepAndScan(-2*range);
  //  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number); // debug
  delay(100);
  
  
  // move half left
  stepAndScan(range);
//  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number); // debug
//  Serial.print("\n"); // debug
  delay(2000);
}

double ping(){
  double distance;
  double duration;
  
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int timeout = 4.0 * 2 / 340.0 * 1e6; // [us] 23529 = 4m both ways
  duration = pulseIn(echoPin, HIGH, timeout); // [us]
  if(duration == 0) {duration = timeout;}
  
  // Calculating the distance
  distance = duration * 340.0 / 2.0 / 10000.0; // [cm]
  return distance;
}


// ********************************
void setup() {
  Serial.begin(9600); // baud rate
  stepper.setSpeed(6); // RPM
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("debug,Setup completed");
}

void loop() {
  if (!digitalRead(switchPin)){
    joystick.manualControl();  
  }
  observe(90);
}
