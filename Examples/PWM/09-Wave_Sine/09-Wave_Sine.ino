// Sine Wave generation using PWM
const int pwmPin = 9; // Must be PWM-capable
const int sineTableSize = 100;
byte sineTable[sineTableSize];

void setup() {
  // Fill sine lookup table
  for (int i = 0; i < sineTableSize; i++) {
    float angle = (2 * 3.14159 * i) / sineTableSize;
    sineTable[i] = (sin(angle) * 127.5) + 127.5; // Convert to 0–255
  }
}

void loop() {
  for (int i = 0; i < sineTableSize; i++) {
    analogWrite(pwmPin, sineTable[i]);
    delayMicroseconds(200); // Adjust for frequency (~50Hz)
  }
}
