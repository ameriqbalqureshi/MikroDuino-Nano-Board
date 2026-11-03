#define BUTTON_PIN 2
#define LED_PIN 13

bool buttonState = HIGH;         // Current button state
bool lastButtonState = HIGH;     // Previous button state
bool ledState = LOW;             // LED state
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // Debounce time in milliseconds

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  bool reading = digitalRead(BUTTON_PIN); // Read button state

  // If button state changes, reset debounce timer
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Check if debounce time has passed and state is stable
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW && buttonState == HIGH) { // Detect a press event
      ledState = !ledState;  // Toggle LED state
      digitalWrite(LED_PIN, ledState);
    }
    buttonState = reading;  // Update stable button state
  }

  lastButtonState = reading;  // Update last raw reading
}
