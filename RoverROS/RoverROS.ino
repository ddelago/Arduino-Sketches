#include <Wire.h>
#include <Servo.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Servo myservo1, myservo2;
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  myservo1.attach(9);
  myservo2.attach(10);
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
  myservo1.write(90);      //Tilt
  myservo2.write(96);      //Pan
}

String input;
char inputRaw;

//Input is D,+000,+000    D,Linear,Angular
float axis5=90, axis5y, linear, angular; 
char linearSign, angularSign;
void loop() {
  // check for incoming serial data:
  if (Serial.available() > 0) {

    //Get Input
    inputRaw = Serial.read();
    if(inputRaw=='D' || inputRaw=='+' || inputRaw=='-' || inputRaw==',' || (inputRaw>=48 && inputRaw <= 57))
      input+=inputRaw;
    //Serial.write(inputRaw);
  }

  //If a valid String, send to controllerInput function
  if(input.length()==11 && input.charAt(0)=='D'){
    //Serial.print(input + "    ");
    controllerInput(input.substring(2));
    input = "";  
  }
  
}

//in: +000,+000
void controllerInput(String in){
  linearSign  = in.charAt(0);
  linear      = ((in.substring(1,4).toInt())/100)*255; //Get Ratio
  angularSign = in.charAt(5);
  angular     = ((in.substring(6).toInt())/100)*192;   //Get Ratio
  
  //If velocity is forward
  if(linearSign=='+'){
    myMotor ->run(BACKWARD);
    myMotor2->run(FORWARD);
    myMotor3->run(BACKWARD);
    myMotor4->run(FORWARD);
    if(angularSign=='+'){               //Turn Right       if axis0==1 which is 0 angular will be 0    
      myMotor ->setSpeed(linear-angular); //Slow Right Side
      myMotor2->setSpeed(linear-angular);
      myMotor3->setSpeed(linear);
      myMotor4->setSpeed(linear);
    }
    else if (angularSign=='-'){          //Turn Left
      myMotor ->setSpeed(linear);
      myMotor2->setSpeed(linear);
      myMotor3->setSpeed(linear-angular); //Slow Left Side
      myMotor4->setSpeed(linear-angular);  
    }
  }
  //If velocity is reverse
  if(linearSign=='-'){
    myMotor ->run(FORWARD);
    myMotor2->run(BACKWARD);
    myMotor3->run(FORWARD);
    myMotor4->run(BACKWARD);
    if(angularSign=='+'){               //Turn Right    if axis0==1 which is 0 angular will be 0
      myMotor ->setSpeed(linear-angular);
      myMotor2->setSpeed(linear-angular);
      myMotor3->setSpeed(linear);
      myMotor4->setSpeed(linear);
    }
    else if (angularSign=='-'){          //Turn Left
      myMotor ->setSpeed(linear);
      myMotor2->setSpeed(linear);
      myMotor3->setSpeed(linear-angular);
      myMotor4->setSpeed(linear-angular);  
    }
  }
  
//Servos_______________________________________________
//  axis2 = (in.substring(18,23).toFloat())*96;
//  axis5y = in.substring(24,29).toFloat();   
//  
//  if(axis5y>1){
//    if(axis5<=165){
//      axis5 += 1;
//      if(axis5y>1.25)
//        axis5 += 2;
//      if(axis5y>1.50)
//        axis5 += 3;
//      if(axis5y>1.75)
//        axis5 += 4;
//    }
//  }
//  if(axis5y<1){
//    if(axis5>=35){
//      axis5 -= 1;
//      if(axis5y<.75)
//        axis5 -= 2;
//      if(axis5y<.50)
//        axis5 -= 3;
//      if(axis5y<.25)
//        axis5 -= 4;
//    }
//  }
//  
//  myservo1.write(axis5);      //Tilt
//  myservo2.write(axis2);      //Pan
  //delay(20);
}










