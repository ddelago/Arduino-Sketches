#define armSpeedFactor 10
void calibration(int calib[])
{
  setArm(1, calib[0]);  
  setArm(2, calib[1]);
  setArm(3, calib[2]);  
  setArm(4, calib[3]);
}

void setArm(int joint, int speedangle)
{
  
  if (joint == 1){
    // Verify it is within limits
    if(speedangle > H10) speedangle = H10;
    else if(speedangle < L10) speedangle = L10;
    // Assign to speed movement variable
    aj1 = speedangle;
    // remap to final value for servos
    speedangle = map(speedangle, 0, 270, 0, 4095);
  }
  else if (joint == 2){
    if(speedangle > H20) speedangle = H20;
    else if(speedangle < L20) speedangle = L20;
    aj2 = speedangle;
    speedangle = map(speedangle, 0, 270, 0, 4095);
  }
  else if (joint == 3){
    if(speedangle > H30) speedangle = H30;
    else if(speedangle < L30) speedangle = L30;
    aj3 = speedangle;
    speedangle = map(speedangle, 0, 270, 4095, 0);
  }
  else if (joint == 4){
    if(speedangle > H40) speedangle = H40;
    else if(speedangle < L40) speedangle = L40;
    aj4 = speedangle;
    speedangle = map(speedangle, 0, 270, 0, 4095);
    
  }
  
  joint = joint * 10; // cause I made the addresses multiples of 10
  word target = speedangle;  //only pass this ints, i tried doing math in this and the remainder error screwed something up
  ArmSerial.write(0xAA); //tells the controller we're starting to send it commands
  ArmSerial.write(joint);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
  ArmSerial.write(0x40 + (target & 0x1F)); //first half of the target, see the pololu jrk manual for more specifics
  ArmSerial.write((target >> 5) & 0x7F);   //second half of the target, " " " 
  
  Serial2.print("setArm joint = ");
  Serial2.print(joint);
  Serial2.print(", final speedangle = ");
  Serial2.println(speedangle);
   
}

void setArmWithSpeed(int joint, int speedangle)
{
  if (joint == 1){
    aj1 = aj1 + (speedangle / armSpeedFactor);
    if(aj1 > H10) aj1 = H10;
    else if(aj1 < L10) aj1 = L10;
    speedangle = aj1;
    speedangle = map(speedangle, 0, 270, 0, 4095);
  }
  else if (joint == 2){
    aj2 = aj2 + (speedangle / armSpeedFactor);
    if(aj2 > H20) aj2 = H20;
    else if(aj2 < L20) aj2 = L20;
    speedangle = aj2;
    speedangle = map(speedangle, 0, 270, 0, 4095);
  }
  else if (joint == 3){
    aj3 = aj3 + (speedangle / armSpeedFactor);
    if(aj3 > H30) aj3 = H30;
    else if(aj3 < L30) aj3 = L30;
    speedangle = aj3;
    speedangle = map(speedangle, 0, 270, 4095, 0);
  }
  else if (joint == 4){
    aj4 = aj4 + (speedangle / armSpeedFactor);
    if(aj4 > H40) aj4 = H40;
    else if(aj4 < L40) aj4 = L40;
    speedangle = aj4;
    speedangle = map(speedangle, 0, 270, 0, 4095);
  }
  
  
  if(joint == 5)
  {
    speedangle = map(speedangle, -100, 100, -255, 255);
    if(abs(speedangle) < 10){speedangle = 0;}
    if(speedangle == 0)
    {
      // set PWM to zero
      analogWrite(ARMwrist, 0);
    }
    else if(speedangle < 0)
    {
      // Set in CCW Direction
      digitalWrite(ARMwrista, HIGH);
      digitalWrite(ARMwristb , LOW);
      delay(5);
      // set PWM to speedangle
      analogWrite(ARMwrist, abs(speedangle));
    }
    else if(speedangle > 0)
    {
      // Set in CCW Direction
      digitalWrite(ARMwrista, LOW);
      digitalWrite(ARMwristb, HIGH);
      delay(5);
      // set PWM to speedangle
      analogWrite(ARMwrist, speedangle);
    }
  }
  else
  {
    joint = joint * 10;
    word target = speedangle;  //only pass this ints, i tried doing math in this and the remainder error screwed something up
    ArmSerial.write(0xAA); //tells the controller we're starting to send it commands
    ArmSerial.write(joint);   //This is the pololu device # you're connected too that is found in the config utility(converted to hex). I'm using #11 in this example
    ArmSerial.write(0x40 + (target & 0x1F)); //first half of the target, see the pololu jrk manual for more specifics
    ArmSerial.write((target >> 5) & 0x7F);   //second half of the target, " " " 
  }
  Serial2.print("setArmWithSpeed joint = ");
  Serial2.print(joint);
  Serial2.print(", final speedangle = ");
  Serial2.println(speedangle);
   
}

