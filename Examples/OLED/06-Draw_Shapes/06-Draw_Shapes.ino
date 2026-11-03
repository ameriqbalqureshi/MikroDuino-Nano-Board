// Draw Shapes on OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();

  // Rectangle
  display.drawRect(10, 10, 50, 30, SSD1306_WHITE);

  // Circle
  display.drawCircle(90, 20, 15, SSD1306_WHITE);

  // Line
  display.drawLine(0, 0, 127, 63, SSD1306_WHITE);

  display.display();
}

void loop() {
  // No animation here
}
