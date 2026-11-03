// MikroDuino Button Read and toggle LED
#define BUTTON_PIN 2  // Button Pin
#define LED_PIN 6     // LED PIN
bool ledState = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}


void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    delay(500);  // Allow time to release button
  }
}