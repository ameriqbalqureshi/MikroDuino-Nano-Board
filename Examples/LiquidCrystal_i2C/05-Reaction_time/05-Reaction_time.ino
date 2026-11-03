// Reaction time game
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin definitions
const int ledPin = 6;
const int buttonPin = 3;

// Timing variables
unsigned long ledOnTime = 0;
unsigned long reactionTime = 0;

bool waitingForReaction = false;
bool lastButtonState = HIGH;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Game!");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Random delay between 2 to 5 seconds
  int delayTime = random(2000, 5000);

  lcd.setCursor(0, 0);
  lcd.print("Get Ready...");
  delay(delayTime);

  // Turn on LED
  digitalWrite(ledPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NOW!");

  // Mark time
  ledOnTime = millis();
  waitingForReaction = true;

  // Wait for user response
  while (waitingForReaction) {
    bool buttonState = digitalRead(buttonPin) == LOW;

    if (buttonState && lastButtonState == HIGH) {
      reactionTime = millis() - ledOnTime;
      waitingForReaction = false;
    }

    lastButtonState = !buttonState ? HIGH : LOW;
  }

  // Turn off LED
  digitalWrite(ledPin, LOW);

  // Display reaction time
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Reaction Time:");
  lcd.setCursor(0, 1);
  lcd.print(reactionTime);
  lcd.print(" ms");

  delay(4000);
  lcd.clear();
}
