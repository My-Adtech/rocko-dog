#include "Arduino.h"
#include "Rocko.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "math.h"

Rocko::Rocko(){
  _pwm = Adafruit_PWMServoDriver();
  _pwm.begin();
  _pwm.setOscillatorFrequency(27000000);
  _pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
  delay(10);
}

void Rocko::Up(){
  print("Hello from Rocko UP");
}

void Rocko::Down(){
  print("Hello from Rocko Down");
}

void Rocko::WriteServo(int servonum, int angleValue){
  _servonum = servonum;
  _angleValue = angleValue;
  _SERVOMIN = SERVOMIN;
  _SERVOMAX = SERVOMAX;

  int _pwmValue = map(_angleValue, 0, 359, _SERVOMIN, _SERVOMAX);
  _pwm.setPWM(_servonum, 0, _pwmValue);
}