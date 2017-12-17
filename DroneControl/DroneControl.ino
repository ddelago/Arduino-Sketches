#include <Wire.h>
#include <Servo.h>

Servo myservo1, myservo2, myservo3, myservo4;

void setup() {
  while (!Serial);    // wait for the serial port to open
  Serial.begin(9600);           // set up Serial library at 9600 bps
  
  myservo1.attach(9);
  myservo2.attach(10);
  myservo3.attach(11);
  myservo4.attach(12);
  
}

String input;
char inputRaw;
//These are axis from controler(Left/Right Analog Stick and R2 and L2 Triggers)
float L2, R2, LX, LY, RX, RY;
void loop() {
  // check for incoming serial data:
  if (Serial.available() > 0) {

    //Get Input
    inputRaw = Serial.read();
    if(inputRaw!='/' && (inputRaw==46 || inputRaw==44 || inputRaw=='S' || inputRaw=='+' || inputRaw=='-' || (inputRaw>=48 && inputRaw <= 57)))
      input+=inputRaw;
    Serial.print(inputRaw);
  }

  //If a valid String, send to controllerInput function
  if(input.length()==42 && input.charAt(0)=='S'){
    Serial.println(input);
    controllerInput(input.substring(1));
    input = "";  
  }
  
}

void controllerInput(String in){
  L2 = 45 + in.substring(1,6).toFloat() * 20;   //Sign does not matter, 45 is min and 155 is max, implement ratio for increased accuracy         
  //Serial.print(L2);
  //Serial.print(" ");
  R2 = 45 + in.substring(7,13).toFloat() * 20;  //Sign does not matter, 45 is min and 155 is max   
  //Serial.print(R2);
  //Serial.print(" ");
  
  if(in.charAt(14)=='+')
    LX = in.substring(15,20).toFloat();         //Left Stick X-Axis
  else if(in.charAt(14)=='-')
    LX = in.substring(15,20).toFloat() * -1;    //Left Stick X-Axis
  //Serial.print(LX);
  //Serial.print(" ");
  
  if(in.charAt(21)=='+')
    LY = in.substring(22,27).toFloat();         //Left Stick Y-Axis
  else if(in.charAt(21)=='-')
    LY = in.substring(22,27).toFloat() * -1;    //Left Stick Y-Axis
  //Serial.print(LY);
  //Serial.print(" ");
  
  if(in.charAt(28)=='+')
    RX = in.substring(29,34).toFloat();         //Right Stick X-Axis
  else if(in.charAt(28)=='-')
    RX = in.substring(29,34).toFloat() * -1;    //Right Stick X-Axis
  //Serial.print(RX);
  //Serial.print(" ");

  if(in.charAt(35)=='+')
    RY = in.substring(36).toFloat();            //Right Stick Y-Axis
  else if(in.charAt(35)=='-')
    RY = in.substring(36).toFloat() * -1;       //Right Stick Y-Axis
  //Serial.print(RY);
  //Serial.print(" ");

  Serial.print(R2);
  Serial.println();

  myservo1.write(R2);
  myservo2.write(R2);
  myservo3.write(R2);
  myservo4.write(R2);
  
}


