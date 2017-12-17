

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  AFMS.begin();  
  myMotor4->run(FORWARD);
  myMotor4->run(RELEASE);
}

String input;
char inputRaw;
float axis3, axis4, velocity;
void loop() {
  if(Serial.available() > 0) {
    inputRaw = Serial.read();
    if(inputRaw!='/' && (inputRaw==46 || inputRaw==44 || inputRaw=='S' || (inputRaw>=48 && inputRaw <= 57)))
      input+=inputRaw;
  
    if(input.length()==30 && input.charAt(0)=='S'){
    //Serial.print(input + "    ");
    controllerInput(input.substring(1));
    input = "";  
  }
}
}

void controllerInput(String in){    
  axis4 = in.substring(6,11).toFloat();
  velocity = (axis4) * 255;

  myMotor4->run(FORWARD);
  myMotor4->setSpeed(velocity);

//    if(inChar=='f'){
//      myMotor4->run(FORWARD);
//      myMotor4->setSpeed(255);
//      delay(50);
//    }
//    if(inChar=='b'){
//      myMotor4->run(BACKWARD);
//      myMotor4->setSpeed(255);
//    }
//    if(inChar=='r'){
//      myMotor4->run(RELEASE);
    
}
