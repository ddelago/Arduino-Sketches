#define insideFactorNumerator 2
#define insideFactorDenominator 3
#define turnFactorNumerator 1
#define turnFactorDenominator 100
#define DstepFactor 5
#define TstepFactor 2

// Simple Version - wheels on each side grouped
void setDrive(int dspeed, int dangle, int estop)
{
  float preciseCspeed;
  Serial2.println("setDrive()");
  Serial2.println(dspeed);
  Serial2.println(dangle);
  Serial2.println(estop);
  // set global variables used in the ramp up feature to these input values
  ddspeed = dspeed;
  ddangle = dangle;
  Serial2.println(cspeed);
  Serial2.println(cangle);
  // check if the current speed and angle are not at the desired speed and angle
  if(cspeed != dspeed || cangle != dangle)
  {
    // if dspeed abs > 5 away cspeed
    if(abs(dspeed - cspeed) > 5 )
    {
      if(dspeed < cspeed)
      {
        cspeed = cspeed - DstepFactor; //  if dspeed is less than current && , subtract step
      }
      else 
      {
        cspeed = cspeed + DstepFactor; //  else if dspeed greater add 5
      }
    }
    else  // else set cspeed to dspeed
    {
      cspeed = dspeed;
    }
    // do same with angle
    if((abs(dangle - cangle)) > 5)
    {
      if(dangle < cangle)
      {
        cangle = cangle - TstepFactor; //  if dangle is less than current && , subtract step
      }
      else 
      {
        cangle = cangle + TstepFactor; //  else if dangle greater add 5
      }
    }
    else  // else set cangle to dangle
    {
      cangle = dangle;
    }
  





    
    // Add a small portion of the difference between current and desired speed/angle
//    preciseCspeed = cspeed;
//    preciseCspeed = preciseCspeed + ((ddspeed - preciseCspeed) / stepFactor);
//    Serial2.print("Better Resolution Cspeed is ");
//    Serial2.print(preciseCspeed);
//    cspeed = cspeed + ((ddspeed - cspeed) / stepFactor);
//    cangle = cangle + ((ddangle - cangle) / stepFactor); 
//    // Check if it is within a small threshold of zero and if so set it to zero
//    //if(abs(cspeed) < 10)cspeed = 0;
//    //if(abs(cangle) < 10)cangle = 0;
//    // check for emergency stop and set speed/angle to zero
    if(estop == 1)
    {
      cspeed = 0;
      cangle = 0;
    }
    Serial2.print("=>");Serial2.println(cspeed);
    Serial2.print("=>");Serial2.println(cangle);

    // get speeds for the laft/right set of wheels by adding/subtracting the angle
    // Get speed for left set of wheels
    int Lspeed = cspeed - cangle; // Simple Version
//    int Lspeed = cspeed - ((cangle * (100 - cspeed)* turnFactorNumerator / turnFactorDenominator)); // speed related version
    if(Lspeed < -100) Lspeed = -100;
    else if(Lspeed > 100) Lspeed = 100;
      
    // Get speed for right set of wheels
    int Rspeed = cspeed + cangle;
//    int Rspeed = cspeed + ((cangle * (100 - cspeed)* turnFactorNumerator / turnFactorDenominator));
    if(Rspeed < -100) Rspeed = -100;
    else if(Rspeed > 100) Rspeed = 100;

    Serial2.print("L/R ");Serial2.print(Lspeed);Serial2.print(" / ");Serial2.println(Rspeed);
    
    Lspeed = map(Lspeed, -100, 100, 0, 127);
    Rspeed = map(Rspeed, -100, 100, 0, 127);

    // Send data to motor drivers
    for(int count = 128; count < 131; count++)
    {
      DriveSerial.write(count);                             // Serial address of driver
      DriveSerial.write(6);                                 // Right side signal
      DriveSerial.write(Lspeed);                            // Right Speed
      DriveSerial.write((count + 6 + Lspeed) & 0b01111111); // Checksum
      DriveSerial.write(count);                             // Serial address of driver
      DriveSerial.write(7);                                 // Left side signal
      DriveSerial.write(Rspeed);                            // Left Speed
      DriveSerial.write((count + 7 + Rspeed) & 0b01111111); // Checksum
    }
  }
}

// Intermediate Version - outside and inside wheels of each side group runn different speeds
//void setDrive(int ddspeed, int ddangle, int estop)
//{
//
//  // Send data to motor drivers
//  if(cspeed != ddspeed || cangle != ddangle)
//  {
//    cspeed = cspeed + ((ddspeed - cspeed) / stepFactor);
//    cangle = cangle + ((ddangle - cangle) / stepFactor); 
//    if(estop == 1)
//    {
//      cspeed = 0;
//      cangle = 0;
//    }
//    
//    int spd = map(cspeed, -100, 100, 0, 127);
//    
//    int LOspeed = spd + (((cangle * turnFactorNumerator) / turnFactorDenominator) * (100 - spd));                     //(spd+(spd/cangle)*(sqrt((cangle-12)*(cangle-12)+361))) !!!!idealistic equation steup in inches!!!!!
//      if(LOspeed < 0) LOspeed = 0;
//      else if(LOspeed > 127) LOspeed = 127;
//      
//    int ROspeed = spd - (((cangle * turnFactorNumerator) / turnFactorDenominator) * (100 - spd));                     //(spd-(spd/cangle)*(sqrt((cangle-12)*(cangle-12)+361)))
//      if(ROspeed < 0) ROspeed = 0;
//      else if(ROspeed > 127) ROspeed = 127;
//   
//    int LIspeed = spd + ((((cangle * turnFactorNumerator) / turnFactorDenominator) * (100 - spd)) * insideFactorNumerator) / insideFactorDenominator;   //(spd+(spd/cangle)*(cangle-12))
//      if(LIspeed < 0) LIspeed = 0;
//      else if(LIspeed > 127) LIspeed = 127;
//      
//    int RIspeed = spd - ((((cangle * turnFactorNumerator) / turnFactorDenominator) * (100 - spd)) * insideFactorNumerator) / insideFactorDenominator;   //(spd-(spd/cangle)*(cangle-12))
//      if(RIspeed < 0) RIspeed = 0;
//      else if(RIspeed > 127) RIspeed = 127;
//
//    // Set drive speed on each pair of wheels through sabertooth drivers
//    
//        DriveSerial.write(128);                              // Serial address of driver
//        DriveSerial.write(6);                                // Right side signal
//        DriveSerial.write(ROspeed);                          // Right Speed
//        DriveSerial.write((128 + 6 + ROspeed) & 0b01111111); // Checksum
//        DriveSerial.write(128);                              // Serial address of driver
//        DriveSerial.write(7);                                // Left side signal
//        DriveSerial.write(LOspeed);                          // Left Speed
//        DriveSerial.write((128 + 7 + LOspeed) & 0b01111111); // Checksum
//
//        DriveSerial.write(129);                              // Serial address of driver
//        DriveSerial.write(6);                                // Right side signal
//        DriveSerial.write(RIspeed);                          // Right Speed
//        DriveSerial.write((129 + 6 + RIspeed) & 0b01111111); // Checksum
//        DriveSerial.write(129);                              // Serial address of driver
//        DriveSerial.write(7);                                // Left side signal
//        DriveSerial.write(LIspeed);                          // Left Speed
//        DriveSerial.write((129 + 7 + LIspeed) & 0b01111111); // Checksum
//
//        DriveSerial.write(130);                              // Serial address of driver
//        DriveSerial.write(6);                                // Right side signal
//        DriveSerial.write(ROspeed);                          // Right Speed
//        DriveSerial.write((130 + 6 + ROspeed) & 0b01111111); // Checksum
//        DriveSerial.write(130);                              // Serial address of driver
//        DriveSerial.write(7);                                // Left side signal
//        DriveSerial.write(LOspeed);                          // Left Speed
//        DriveSerial.write((130 + 7 + LOspeed) & 0b01111111); // Checksum
//  }
//}

// Advanced Version - each wheels velocity for its individual arc radius is calculated

// Final Version - traction control system, detecting wheel slip and angle of suspension arms, transferring power to the wheels that need it

