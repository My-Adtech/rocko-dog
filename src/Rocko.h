/*
  Rocko.h - Library for the STEM robot dog Rocko.
  Created by MYADTECH.
  Engineers Marco Andrade & Rodrigo Villanueva, November 04, 2021.
*/
#ifndef Rocko_h
#define Rocko_h

#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_PWMServoDriver.h"
#include "math.h"

//This values are for SG90, change values according to your servos
#define SERVOMIN  200 // This is the 'minimum' pulse length count (out of 4096)= 0°
#define SERVOMAX  577 // This is the 'maximum' pulse length count (out of 4096)= 180°
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

class Rocko
{
  public:
    Rocko();
    void Up();
    void Down();
  private:
    Adafruit_PWMServoDriver _pwm;
    int _pwmValue;
    void WriteServo(int servonum, int, angleValue);
};

#endif
