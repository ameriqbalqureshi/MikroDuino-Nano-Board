// MikroDuino Nano LED Random
// Set LEDs from D6 to D13 on Random
void setup() {
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}
// LED Random
void loop() {
  int led = random(6, 14);
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

