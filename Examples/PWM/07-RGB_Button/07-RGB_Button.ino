//RGB LED Color selection using Button
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 2;

int mode = 0;
bool lastButtonState = HIGH;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    mode++;
    if (mode > 6) mode = 0;
    delay(200); // debounce
  }
  lastButtonState = buttonState;

  switch (mode) {
    case 0: setColor(255, 0, 0); break;   // Red
    case 1: setColor(0, 255, 0); break;   // Green
    case 2: setColor(0, 0, 255); break;   // Blue
    case 3: setColor(255, 255, 0); break; // Yellow
    case 4: setColor(0, 255, 255); break; // Cyan
    case 5: setColor(255, 0, 255); break; // Magenta
    case 6: setColor(255, 255, 255); break; // White
  }
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
