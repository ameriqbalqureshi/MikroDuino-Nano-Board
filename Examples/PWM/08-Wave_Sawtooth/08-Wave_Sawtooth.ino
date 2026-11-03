// Sawtooth Wave useing PWM
const int pwmPin = 5;       // PWM-capable pin (pins 5 or 6 have ~980Hz PWM)
const int maxValue = 255;   // 8-bit PWM range

void setup() {
  pinMode(pwmPin, OUTPUT);
}

void loop() {
  for (int value = 0; value <= maxValue; value++) {
    analogWrite(pwmPin, value);  // Set PWM duty cycle
    delayMicroseconds(200);      // Controls the frequency of the wave
  }
}
