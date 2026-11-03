#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Create LCD object at I2C address 0x27, for a 16x2 display
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pins
const int incButtonPin = 3;   // S3 on mikroduino board
const int decButtonPin = 4;   // S4

// Variables
int counter = 0;
bool lastIncState = HIGH;
bool lastDecState = HIGH;

void setup() {
  lcd.init();             // Initialize LCD
  lcd.backlight();        // Turn on backlight
  lcd.setCursor(0, 0);
  lcd.print("Counter:");

  pinMode(incButtonPin, INPUT_PULLUP);
  pinMode(decButtonPin, INPUT_PULLUP);

  displayCounter();
}

void loop() {
  // Read current button states
  bool incPressed = digitalRead(incButtonPin) == LOW;
  bool decPressed = digitalRead(decButtonPin) == LOW;

  // Check if increment button was pressed
  if (incPressed && lastIncState == HIGH) {
    counter++;
    displayCounter();
    delay(200);  // debounce delay
  }
  lastIncState = !incPressed ? HIGH : LOW;

  // Check if decrement button was pressed
  if (decPressed && lastDecState == HIGH) {
    counter--;
    displayCounter();
    delay(200);  // debounce delay
  }
  lastDecState = !decPressed ? HIGH : LOW;
}

// Function to display counter value
void displayCounter() {
  lcd.setCursor(0, 1);
  lcd.print("Value:         "); // Clear old value
  lcd.setCursor(7, 1);
  lcd.print(counter);
}
