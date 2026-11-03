//ADC brightness with potentiometer
const int potPin = A7;    // Potentiometer pin
const int ledPin = 9;     // PWM pin connected to LED

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int sensorValue = analogRead(potPin);          // 0 to 1023
  int pwmValue = map(sensorValue, 0, 1023, 0, 255); // Scale to 0–255
  analogWrite(ledPin, pwmValue);
}
