// RGB Mixing using potentiometers
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

const int potRed = A0;
const int potGreen = A1;
const int potBlue = A2;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  int rVal = analogRead(potRed);
  int gVal = analogRead(potGreen);
  int bVal = analogRead(potBlue);

  analogWrite(redPin, map(rVal, 0, 1023, 0, 255));
  analogWrite(greenPin, map(gVal, 0, 1023, 0, 255));
  analogWrite(bluePin, map(bVal, 0, 1023, 0, 255));

  delay(10);
}
