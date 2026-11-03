//Button press counter
// S3 Increment S4 Decrement
// Counter limit 0 to 20
// Long Press of S3 reset counter
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define BUTTON_INC 3
#define BUTTON_DEC 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int counter = 0;
const int minCount = 0;
const int maxCount = 20;

unsigned long lastPressInc = 0;
unsigned long lastPressDec = 0;
bool incHandled = false;
bool decHandled = false;

const unsigned long longPressTime = 1500;

void setup() {
  pinMode(BUTTON_INC, INPUT_PULLUP);
  pinMode(BUTTON_DEC, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  updateDisplay();
}

void loop() {
  handleButton(BUTTON_INC, 1, lastPressInc, incHandled);
  handleButton(BUTTON_DEC, -1, lastPressDec, decHandled);
}

void handleButton(int pin, int direction, unsigned long &lastPress, bool &handled) {
  bool isPressed = digitalRead(pin) == LOW;

  if (isPressed) {
    if (!handled) {
      lastPress = millis();
      // Apply short press immediately
      counter += direction;
      counter = constrain(counter, minCount, maxCount);
      updateDisplay();
      handled = true;
    } else if (millis() - lastPress >= longPressTime) {
      // Long press reset
      counter = 0;
      updateDisplay();
      handled = true; // avoid multiple resets
    }
  } else {
    // Reset flags when button is released
    handled = false;
  }
}

void updateDisplay() {
  display.clearDisplay();
  display.setCursor(10, 20);
  display.print("Count: ");
  display.print(counter);
  display.display();
}
