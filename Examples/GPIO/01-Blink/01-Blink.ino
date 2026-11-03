// MikroDuino Nano LED Chase
// Chase LEDs from D6 to D13
void setup() {
  for(int i=6;i<14;i++){
    pinMode(6, OUTPUT);
  }
 }


void loop() {
  // Turning LEds ON one by One
  for(int a=6;a<14;a++){
    digitalWrite(a, HIGH);
    delay(500);
  }
// Turning LEds OFF one by One
  for(int a=6;a<14;a++){
    digitalWrite(a, LOW);
    delay(500);
  }
}
