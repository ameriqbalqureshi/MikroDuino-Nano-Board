#define BUTTON_PIN 2
#define LED_PIN 13

volatile bool buttonPressed = false;  // Flag for button press
unsigned long lastDebounceTime = 0;   // Stores last valid press time
const unsigned long debounceDelay = 50;  // Debounce time in milliseconds

void handleButtonPress() {  
  unsigned long currentTime = millis();
  
  // Debounce: Accept only if enough time has passed
  if (currentTime - lastDebounceTime > debounceDelay) {  
    buttonPressed = true;  // Set flag for processing in loop()
    lastDebounceTime = currentTime;  
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonPress, FALLING);
}

void loop() {
  if (buttonPressed) {  
    buttonPressed = false;  // Reset flag
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));  // Toggle LED
  }
}
