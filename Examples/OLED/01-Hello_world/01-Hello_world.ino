#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display size (width, height)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address for SSD1306 (common one is 0x3C)
#define OLED_ADDRESS 0x3C

// Create display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);  // -1 means no reset pin

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
    // Clear buffer
  display.clearDisplay();

  // Set text size and color
  display.setTextSize(1);      // Size: 1 = small, 2 = medium, 3 = large
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);    // (x, y)

  // Print message
  display.println("Hello, World!");

  // Show on screen
  display.display();
}

void loop() {
  // Nothing to repeat
}
