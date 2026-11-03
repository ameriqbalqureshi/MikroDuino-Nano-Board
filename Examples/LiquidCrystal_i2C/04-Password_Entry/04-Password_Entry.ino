// Password Entry System
// S3 increment a digit, S3 confirms
// After 4 digits value is compared

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button and LED pins
const int incButtonPin = 3;
const int nextButtonPin = 4;
const int ledPin = 6;

// Password variables
const int password[4] = {1, 2, 3, 4};  // Pre-stored password
int entered[4];
int currentDigit = 0;
int position = 0;

bool lastIncState = HIGH;
bool lastNextState = HIGH;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(incButtonPin, INPUT_PULLUP);
  pinMode(nextButtonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  lcd.print("____");
}

void loop() {
  bool incPressed = digitalRead(incButtonPin) == LOW;
  bool nextPressed = digitalRead(nextButtonPin) == LOW;

  // Handle increment button (digit change)
  if (incPressed && lastIncState == HIGH) {
    currentDigit = (currentDigit + 1) % 10;
    updateDisplay();
    delay(200);
  }
  lastIncState = !incPressed ? HIGH : LOW;

  // Handle next button (digit confirm)
  if (nextPressed && lastNextState == HIGH) {
    entered[position] = currentDigit;
    position++;
    delay(200);

    if (position >= 4) {
      checkPassword();
      resetSystem();
    } else {
      currentDigit = 0;
      updateDisplay();
    }
  }
  lastNextState = !nextPressed ? HIGH : LOW;
}

void updateDisplay() {
  lcd.setCursor(position, 1);
  lcd.print(currentDigit);
}

void checkPassword() {
  bool correct = true;
  for (int i = 0; i < 4; i++) {
    if (entered[i] != password[i]) {
      correct = false;
      break;
    }
  }

  lcd.clear();
  if (correct) {
    lcd.print("Access Granted");
    digitalWrite(ledPin, HIGH);
  } else {
    lcd.print("Access Denied");
  }

  delay(2000);
}

void resetSystem() {
  // Reset everything
  currentDigit = 0;
  position = 0;
  for (int i = 0; i < 4; i++) entered[i] = 0;

  digitalWrite(ledPin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
  lcd.setCursor(0, 1);
  lcd.print("____");
}
