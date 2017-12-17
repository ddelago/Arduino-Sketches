// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar1(10, 9, MAX_DISTANCE);

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
}

double ping1, ping2;
void loop() {
  
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  ping1 = sonar.ping_cm();
  ping2 = sonar1.ping_cm();
  
  Serial.print("Ping1: ");
  if(ping1==0.00){
    Serial.println("Out Of Range"); // Send ping, get distance in cm and print result (0 = outside set distance range)  
  }
  else{
    Serial.print(ping1);
    Serial.println("cm");
  }
  
  Serial.print("Ping2: ");
  if(ping2==0.00){
    Serial.println("Out Of Range"); // Send ping, get distance in cm and print result (0 = outside set distance range)  
  }
  else{
    Serial.print(ping2);
    Serial.println("cm");
  }
  
  
}
