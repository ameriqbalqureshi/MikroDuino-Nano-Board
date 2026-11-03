// MikroDuino Nano LED Chase
// Chase LEDs from D6 to D13
void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
  }
}
// LED Binary
void loop() {
  int count = 210;
  for (int i = 0; i < 8; i++) {
    digitalWrite(i + 6, (count >> i) & 1);
  }
}