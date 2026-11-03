// MikroDuino Nano LED Chase
// Chase LEDs from D6 to D13
void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}

// LED Ping Pong Back and Forth
void loop() {
    for (int i = 6; i <= 13; i++) {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
  for (int i = 12; i > 6; i--) {
    digitalWrite(i, HIGH);
    delay(100);
    digitalWrite(i, LOW);
  }
}
