/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/

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
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  
  //myMotor->setSpeed(150);
  myMotor->run(BACKWARD);
  myMotor2->run(FORWARD);
  myMotor3->run(BACKWARD);
  myMotor4->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  myMotor2->run(RELEASE);
  myMotor3->run(RELEASE);
  myMotor4->run(RELEASE);
}

void loop() {
  uint8_t i;
  if(Serial.available() > 0) {
    char inChar = (char)Serial.read();
    while(inChar!='b'){
      if(inChar=='w'){
        myMotor->run(BACKWARD);
        myMotor2->run(FORWARD);
        myMotor3->run(BACKWARD);
        myMotor4->run(FORWARD);
        for (i=0; i<255; i++) {
          myMotor->setSpeed(i);
          myMotor2->setSpeed(i);
          myMotor3->setSpeed(i);
          myMotor4->setSpeed(i);  
          delay(10);
        }
      }
      
      if(inChar=='s'){
        myMotor->run(FORWARD);
        myMotor2->run(BACKWARD);
        myMotor3->run(FORWARD);
        myMotor4->run(BACKWARD);
        for (i=0; i<255; i++) {
          myMotor->setSpeed(i);
          myMotor2->setSpeed(i);
          myMotor3->setSpeed(i);
          myMotor4->setSpeed(i);
          delay(10);  
        }
      }

      inChar = (char)Serial.read();
    }
    
    myMotor->setSpeed(0);
    myMotor2->setSpeed(0);
    myMotor3->setSpeed(0);
    myMotor4->setSpeed(0);
    
    myMotor->run(RELEASE);
    myMotor2->run(RELEASE);
    myMotor3->run(RELEASE);
    myMotor4->run(RELEASE);
  }
  
}
