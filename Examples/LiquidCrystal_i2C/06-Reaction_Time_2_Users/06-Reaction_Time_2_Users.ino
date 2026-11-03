// Two User reaction time
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pins
const int ledPin = 6;
const int button1Pin = 3;  // Player 1
const int button2Pin = 4;  // Player 2

// Variables
unsigned long ledOnTime = 0;
unsigned long p1Time = 0, p2Time = 0;
bool ledOn = false;
bool p1Pressed = false;
bool p2Pressed = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Reaction Duel!");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Get Ready...");
  delay(random(2000, 5000)); // Random delay

  // Start signal
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GO!");
  digitalWrite(ledPin, HIGH);
  ledOnTime = millis();
  ledOn = true;

  // Wait for either player to press
  while (!(p1Pressed || p2Pressed)) {
    if (!p1Pressed && digitalRead(button1Pin) == LOW) {
      p1Time = millis() - ledOnTime;
      p1Pressed = true;
    }
    if (!p2Pressed && digitalRead(button2Pin) == LOW) {
      p2Time = millis() - ledOnTime;
      p2Pressed = true;
    }
  }

  digitalWrite(ledPin, LOW);
  lcd.clear();

  // Determine winner
  if (p1Pressed && !p2Pressed) {
    lcd.print("Player 1 Wins!");
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(p1Time);
    lcd.print(" ms");
  } else if (p2Pressed && !p1Pressed) {
    lcd.print("Player 2 Wins!");
    lcd.setCursor(0, 1);
    lcd.print("Time: ");
    lcd.print(p2Time);
    lcd.print(" ms");
  } else if (p1Pressed && p2Pressed) {
    if (p1Time < p2Time) {
      lcd.print("Player 1 Wins!");
      lcd.setCursor(0, 1);
      lcd.print("P1: ");
      lcd.print(p1Time);
      lcd.print(" ms");
    } else if (p2Time < p1Time) {
      lcd.print("Player 2 Wins!");
      lcd.setCursor(0, 1);
      lcd.print("P2: ");
      lcd.print(p2Time);
      lcd.print(" ms");
    } else {
      lcd.print("It's a Tie!");
      lcd.setCursor(0, 1);
      lcd.print(p1Time);
      lcd.print(" ms");
    }
  }

  // Reset game
  delay(4000);
  p1Pressed = p2Pressed = false;
  p1Time = p2Time = 0;
  lcd.clear();
}
