#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();

  // Display large text
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("BIG!");
  display.display();
  delay(2000);

  // Scroll demo
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Scrolling right...");
  display.display();
  display.startscrollright(0x00, 0x0F);
  delay(3000);
  display.stopscroll();

  // Animated text bounce
  String msg = "Bouncing Text!";
  int x = 0;
  int dx = 2;

  for (int i = 0; i < 100; i++) {
    display.clearDisplay();
    display.setCursor(x, 30);
    display.setTextSize(1);
    display.println(msg);
    display.display();
    delay(100);
    x += dx;
    if (x < 0 || x > (SCREEN_WIDTH - msg.length() * 6)) dx = -dx;
  }
}

void loop() {
  // Nothing in loop
}
