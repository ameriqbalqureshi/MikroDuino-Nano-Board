//PWM RGB LEDs
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Fade red up, others off
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, i);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    delay(10);
  }

  // Fade green up, red down
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 255 - i);
    analogWrite(greenPin, i);
    analogWrite(bluePin, 0);
    delay(10);
  }

  // Fade blue up, green down
  for (int i = 0; i <= 255; i++) {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255 - i);
    analogWrite(bluePin, i);
    delay(10);
  }

  // White light mix (R + G + B full)
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  delay(1000);

  // All off
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(1000);
}
