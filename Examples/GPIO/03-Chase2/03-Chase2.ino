// MikroDuino Nano LED Chase
// Chase LEDs from D6 to D13
void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}


void loop() {
// One LED Chase
  for (int i = 6; i <= 13; i++) {
    digitalWrite(i, HIGH);
    delay(200);
    digitalWrite(i, LOW);
  }
}
