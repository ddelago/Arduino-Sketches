

void setup() {
  // open the serial port:
  Serial.begin(9800);
}
String input;
char inChar;
void loop() {
  
  inChar = Serial.read();

  while(inChar == 'C' || inChar == 'D' || inChar == 'R' || inChar == 'A' || (inChar>=48 && inChar <= 57)|| inChar == ',' || inChar == '.' || inChar == '+' || inChar == '-' ){
    if(inChar=='D' || inChar=='C')
      Serial.println();
      Serial.print(inChar);
      inChar = Serial.read();
  }
}
