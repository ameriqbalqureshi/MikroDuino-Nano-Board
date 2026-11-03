// Counter with reset on long press for 2 seconds of S3
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pins
const int incButtonPin = 3;
const int decButtonPin = 4;

// Variables
int counter = 0;
bool lastIncState = HIGH;
bool lastDecState = HIGH;

unsigned long buttonPressStart = 0;
bool longPressHandled = false;
const unsigned long longPressDuration = 2000; // 2 seconds

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Counter:");

  pinMode(incButtonPin, INPUT_PULLUP);
  pinMode(decButtonPin, INPUT_PULLUP);

  displayCounter();
}

void loop() {
  // ----- Increment Button -----
  bool incPressed = digitalRead(incButtonPin) == LOW;

  if (incPressed) {
    if (lastIncState == HIGH) {
      // Button just pressed
      buttonPressStart = millis();
      longPressHandled = false;
    } else {
      // Button is being held
      if (!longPressHandled && (millis() - buttonPressStart > longPressDuration)) {
        counter = 0;  // Reset the counter
        displayMessage("Counter Reset!");
        displayCounter();
        longPressHandled = true;
      }
    }
  } else if (lastIncState == LOW && !longPressHandled) {
    // Button was released quickly – count as normal press
    counter++;
    displayCounter();
    delay(200);  // debounce
  }
  lastIncState = !incPressed ? HIGH : LOW;

  // ----- Decrement Button -----
  bool decPressed = digitalRead(decButtonPin) == LOW;

  if (decPressed && lastDecState == HIGH) {
    counter--;
    displayCounter();
    delay(200); // debounce
  }
  lastDecState = !decPressed ? HIGH : LOW;
}

// Show the current counter value
void displayCounter() {
  lcd.setCursor(0, 1);
  lcd.print("Value:         ");
  lcd.setCursor(7, 1);
  lcd.print(counter);
}

// Temporary message function
void displayMessage(String msg) {
  lcd.setCursor(0, 1);
  lcd.print(msg);
  delay(1000);
}
