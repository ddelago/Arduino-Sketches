
#include <NewPing.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);
Adafruit_DCMotor *myMotor3 = AFMS.getMotor(3);
Adafruit_DCMotor *myMotor4 = AFMS.getMotor(4);

NewPing sonar1(12, 11, 20); //Front: Trigger, Echo, Max Distance
NewPing sonar2(10, 9, 20);  //Left
NewPing sonar3(8, 7, 20);   //Right

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
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

double frontSensor, leftSensor, rightSensor;
int path = 1;    //1: no obstacles
void loop() {
  //50ms between pings (20 pings/sec)
  pingSensors();

  //An obstacle was detected
  if((frontSensor>0 && frontSensor<10) || (leftSensor>0 && leftSensor<10) || (rightSensor>0 && rightSensor<10)){
    path = 0;
  }

  //Until a good path is found
  while(path==0){
    findNewPath();
  }
  
  moveForward();
  
}

void pingSensors(){

  frontSensor = sonar1.ping_cm();
  Serial.print("Front: ");
  Serial.print(frontSensor);
  Serial.println("cm");

  leftSensor = sonar2.ping_cm();
  Serial.print("Left: ");
  Serial.print(leftSensor);
  Serial.println("cm\n");

  rightSensor = sonar3.ping_cm();
  Serial.print("Right: ");
  Serial.print(rightSensor);
  Serial.println("cm\n");
  
}

void findNewPath(){
  
  pingSensors();

  //If left is clear
  if(leftSensor==0){
    turnLeft();
  }
  //If the right is clear
  else if(rightSensor==0){
    turnRight();
  }

  //Check for obstacles
  pingSensors();

  //If path clear
  if(frontSensor==0 && (leftSensor==0 || leftSensor>5) && (rightSensor==0 || rightSensor>5)){
    path = 1;
    return;
  }

  //If an obstacle, find new path
  findNewPath();
}

void moveForward(){
  myMotor->run(FORWARD);       //Right Side
  myMotor2->run(FORWARD);      //Right Side
  myMotor3->run(FORWARD);      //Left Side
  myMotor4->run(FORWARD);      //Left Side
  myMotor ->setSpeed(192);
  myMotor2->setSpeed(192);
  myMotor3->setSpeed(192);
  myMotor4->setSpeed(192); 
  delay(30);
}

void moveBackward(){
  myMotor->run(BACKWARD);       //Right Side
  myMotor2->run(BACKWARD);      //Right Side
  myMotor3->run(BACKWARD);      //Left Side
  myMotor4->run(BACKWARD);      //Left Side
  myMotor ->setSpeed(192);
  myMotor2->setSpeed(192);
  myMotor3->setSpeed(192);
  myMotor4->setSpeed(192); 
 
}

void turnLeft(){
  myMotor->run(BACKWARD);       //Right Side
  myMotor2->run(BACKWARD);      //Right Side
  myMotor3->run(BACKWARD);      //Left Side
  myMotor4->run(BACKWARD);      //Left Side
  myMotor ->setSpeed(96);
  myMotor2->setSpeed(96);
  myMotor3->setSpeed(192);
  myMotor4->setSpeed(192); 
  delay(1000);

  myMotor->run(FORWARD);       //Right Side
  myMotor2->run(FORWARD);      //Right Side
  myMotor3->run(FORWARD);      //Left Side
  myMotor4->run(FORWARD);      //Left Side
  myMotor ->setSpeed(192);
  myMotor2->setSpeed(192);
  myMotor3->setSpeed(96);
  myMotor4->setSpeed(96); 
  delay(750);

}

void turnRight(){
  myMotor->run(BACKWARD);       //Right Side
  myMotor2->run(BACKWARD);      //Right Side
  myMotor3->run(BACKWARD);      //Left Side
  myMotor4->run(BACKWARD);      //Left Side
  myMotor ->setSpeed(192);
  myMotor2->setSpeed(192);
  myMotor3->setSpeed(96);
  myMotor4->setSpeed(96); 
  delay(1000);

  myMotor->run(FORWARD);       //Right Side
  myMotor2->run(FORWARD);      //Right Side
  myMotor3->run(FORWARD);      //Left Side
  myMotor4->run(FORWARD);      //Left Side
  myMotor ->setSpeed(96);
  myMotor2->setSpeed(96);
  myMotor3->setSpeed(192);
  myMotor4->setSpeed(192); 
  delay(750);

}







