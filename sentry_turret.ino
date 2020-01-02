#include "Stepper.h"
#include "Joystick.h"
#include "config.h"

// Motor
Stepper stepper(STEPS, 8, 10, 9, 11);

// Joystick
Joystick joystick(A0, A1, switchPin, stepper);

// Other
int it = 0; // iteration counter

// ******** Functions ********
int angleToStep(double a){
  return a/360.0*STEPS;
}

int sgn(int val){
  return (0 < val) - (val < 0);
}

void stepAndScan(int steps){
  steps = steps - steps % minStep;
  for(int i = 0; i < abs(steps); i += minStep){
    stepper.step(sgn(steps)*minStep);
    ping();
  }
}

void observe(double angleOfView){
  int range = angleToStep(angleOfView)/2.0;
  
  // move half left
  stepAndScan(range);
  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number);
  delay(100);
  
  
  // move full right
  stepAndScan(-2*range);
  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number);
  delay(100);
  
  
  // move half left
  stepAndScan(range);
  Serial.print(it);Serial.print("\tstep_number: ");Serial.println(stepper.step_number);
  Serial.print("\n");
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
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration*0.034/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.print("\tstep_number: ");
  Serial.print(stepper.step_number);
  Serial.print("\n");
  return distance;
}


// ********************************
void setup() {
  Serial.begin(9600); // baud rate
  stepper.setSpeed(6); // RPM
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("setup completed");
}

void loop() {
  if (!digitalRead(switchPin)){
    joystick.manualControl();  
  }
  observe(90);
  it++;
}
