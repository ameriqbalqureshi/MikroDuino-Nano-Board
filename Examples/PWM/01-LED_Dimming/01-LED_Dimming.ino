// PWM DEMO
// Pin connected to LED
const int ledPin = 9; // Use any PWM pin (e.g., 3, 5, 6, 9, 10, 11 on UNO)

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Increase brightness
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(10);
  }

  // Decrease brightness
  for (int brightness = 255; brightness >= 0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10);
  }
}
