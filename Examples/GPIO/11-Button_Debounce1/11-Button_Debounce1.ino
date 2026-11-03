// Button Debounce using Delay
#define BUTTON_PIN 2
#define LED_PIN 13

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // Button Pressed
    delay(50);  // Simple debounce delay
    if (digitalRead(BUTTON_PIN) == LOW) {  // Confirm press
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // Toggle LED
    }
    while (digitalRead(BUTTON_PIN) == LOW);  // Wait for button release
  }
}
