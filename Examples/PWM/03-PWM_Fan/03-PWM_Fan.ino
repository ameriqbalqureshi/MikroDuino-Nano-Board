// PWM Fan Speed Control
const int fanPin = 10; // PWM pin connected to transistor base via resistor

void setup() {
  pinMode(fanPin, OUTPUT);
}

void loop() {
  // Ramp up
  for (int speed = 0; speed <= 255; speed++) {
    analogWrite(fanPin, speed);
    delay(10);
  }

  // Ramp down
  for (int speed = 255; speed >= 0; speed--) {
    analogWrite(fanPin, speed);
    delay(10);
  }

  delay(1000);
}
