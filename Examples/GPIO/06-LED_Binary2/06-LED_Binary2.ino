// MikroDuino Nano LED Binary Counter
// Chase LEDs from D6 to D13
void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}
// LED Binary Counter
void loop() {
  for (int count = 0; count < 256; count++) {
    for (int i = 0; i < 8; i++) {
      digitalWrite(i + 6, (count >> i) & 1);
    }
    delay(250);
  }
}
