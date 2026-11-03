// MikroDuino Nano Knight Rider LED Smooth Scrolling

void setup() {
    for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); // Set LED OFF
  }
}
int delayTime = 100; // Global variable
void loop() {
  for (int i = 6; i <= 12; i++) {
    digitalWrite(i, HIGH);
    digitalWrite(i + 1, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
  for (int i = 13; i >= 7; i--) {
    digitalWrite(i, HIGH);
    digitalWrite(i - 1, HIGH);
    delay(delayTime);
    digitalWrite(i, LOW);
  }
}


int leds[8]={2,8,5,4,7};
