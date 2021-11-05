#include "Rocko.h"

Rocko rocko;

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//This values are for SG90
#define SERVOMIN  200 // This is the 'minimum' pulse length count (out of 4096)= 0°
#define SERVOMAX  577 // This is the 'maximum' pulse length count (out of 4096)= 180°
#define USMIN  500 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

float GetAlphaAng(int);
float GetBettaAng(int);
float GetGammaAng(int);
void WriteServo(int, int);
void UpDown(int);
void GetError(int, int);

float femur = 10; //Dimensions in cm
float calf = 10;  //Dimensions in cm
float desired_height[2] = {0}; //Dimensions in cm per leg

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  //Serial.println("Hello from Doggy");

  //pwm.begin();
  //pwm.setOscillatorFrequency(27000000);
  //pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  //delay(2000);
}

void loop() {
  rocko.Up();
  //UpDown(11); //Dimensions in cm
  delay(2000);
  rocko.Down();
  //UpDown(7); //Dimensions in cm
  delay(2000);
}

float GetAlphaAng(int n){
  float alpha = acos((pow(calf, 2) + pow(desired_height[n], 2) - pow(femur, 2)) / (2 * calf * desired_height[n]));
  return alpha;
}

float GetBetaAng(int n){
  float beta = acos((pow(femur, 2) + pow(desired_height[n], 2) - pow(calf, 2)) / (2 * femur * desired_height[n]));
  return beta;
}

float GetGammaAng(int n){
  float gamma = acos((pow(femur, 2) + pow(calf, 2) - pow(desired_height[n], 2)) / (2 * calf * femur));
  return gamma;
}


void WriteServo(int servonum, int angleValue){
  int pwmValue = map(angleValue, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(servonum, 0, pwmValue);
}


void UpDown(int h){
  float alpha, beta, gamma;
  int alphaDeg, betaDeg, gammaDeg, thetaDeg;

  for (int i = 0; i < 2; i++){
    desired_height[i] = h;
  }

  for (int i = 0; i < 2; i++){
    alpha = GetAlphaAng(i);
    beta  = GetBetaAng(i);
    gamma = GetGammaAng(i);

    alphaDeg = round(alpha * 57.2957);
    betaDeg = round(beta * 57.2957);
    gammaDeg = round(gamma * 57.2957);
    
    thetaDeg = 180 - betaDeg;
    
    WriteServo(i, thetaDeg); //Femur
    WriteServo((i*2), gammaDeg); //Calf
  }
}
