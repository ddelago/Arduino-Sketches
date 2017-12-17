#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  //Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  
  myMotor->run(BACKWARD);       //Right Side
  myMotor2->run(FORWARD);       //Right Side
  myMotor3->run(BACKWARD);      //Left Side
  myMotor4->run(FORWARD);       //Left Side
  // turn on motor
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
}

String input;
char inputRaw;
float axis3, axis4, axis0, velocity, angular;
void loop() {
  // check for incoming serial data:
  if (Serial.available() > 0) {
    
    inputRaw = Serial.read();
    if(inputRaw!='/' && (inputRaw==46 || inputRaw==44 || inputRaw=='S' || (inputRaw>=48 && inputRaw <= 57)))
      input+=inputRaw;
    //Serial.write(inputRaw);
  }
  
  if(input.length()==18 && input.charAt(0)=='S'){
    //Serial.print(input + "    ");
    controllerInput(input.substring(1));
    input = "";  
  }
  
}

void controllerInput(String in){
  axis3 = in.substring(0,5).toFloat();
  axis4 = in.substring(6,11).toFloat();
  axis0 = in.substring(12,17).toFloat();
  velocity = (axis4 - axis3) * 255;
  //Serial.print(String(axis4) + "," + String(axis3));
  //Serial.print("     ");
   
  if(velocity>=0){
    myMotor ->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
    if(axis0>=1){               //Turn Right 
      angular = 192*(axis0-1);  //Turn Right     if axis0==1 which is 0 angular will be 0
      myMotor ->setSpeed(velocity-angular);
      myMotor2->setSpeed(velocity-angular);
      myMotor3->setSpeed(velocity);
      myMotor4->setSpeed(velocity);
    }
    else if (axis0<1){          //Turn Left
      angular = 192*(1-axis0);  //Turn Left
      myMotor ->setSpeed(velocity);
      myMotor2->setSpeed(velocity);
      myMotor3->setSpeed(velocity-angular);
      myMotor4->setSpeed(velocity-angular);  
    }
    delay(40);
  }
    
  if(velocity<0){
    velocity = abs(velocity);
    myMotor ->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
    if(axis0>=1){               //Turn Right
      angular = 192*(axis0-1);  //Turn Right     if axis0==1 which is 0 angular will be 0
      myMotor ->setSpeed(velocity-angular);
      myMotor2->setSpeed(velocity-angular);
      myMotor3->setSpeed(velocity);
      myMotor4->setSpeed(velocity);
    }
    else if (axis0<1){          //Turn Left
      angular = 192*(1-axis0);  //Turn Left
      myMotor ->setSpeed(velocity);
      myMotor2->setSpeed(velocity);
      myMotor3->setSpeed(velocity-angular);
      myMotor4->setSpeed(velocity-angular);  
    }
    delay(40);
  }
  
}










