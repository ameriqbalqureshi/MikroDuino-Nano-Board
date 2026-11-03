#define BUTTON_PIN 2
#define LED_PIN 13

bool lastButtonState = HIGH;  // Previous button state

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {  // Detect press
    delay(50);  // Debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) {  // Confirm press after delay
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // Toggle LED
    }
  }
  lastButtonState = buttonState;  // Update button state
}
