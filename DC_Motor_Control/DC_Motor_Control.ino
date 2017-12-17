void setup() {
  
  pinMode(6, OUTPUT); //Left
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  //pinMode(5, OUTPUT);
  //pinMode(6, OUTPUT);
  //pinMode(7, OUTPUT); //Right
}

void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);
  //digitalWrite(5, HIGH);
  //digitalWrite(6, LOW);
  //analogWrite(2, 255);
  analogWrite(7, 255);
  delay(500);
  
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  //digitalWrite(5, LOW);
  //digitalWrite(6, HIGH);
  delay(500);
}
