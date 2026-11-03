// Binary Clock
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

// Size of each block
#define BLOCK_SIZE 8
#define BLOCK_SPACING 2

void setup() {
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  DateTime now = rtc.now();

  display.clearDisplay();
  drawBinaryTime(now.hour(), now.minute(), now.second());
  display.display();
  
  delay(500);
}

void drawBinaryTime(int hour, int minute, int second) {
  drawBinaryColumn(hour, 0);
  drawBinaryColumn(minute, 1);
  drawBinaryColumn(second, 2);

  // Label the columns
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 58);
  display.print("H");
  display.setCursor(54, 58);
  display.print("M");
  display.setCursor(98, 58);
  display.print("S");
}

void drawBinaryColumn(int value, int column) {
  int x_offset = column * 44 + 6; // Adjust column spacing

  for (int i = 0; i < 6; i++) { // 6 bits (enough for 0-59 or 0-23)
    int bit = (value >> i) & 0x01;

    int y = 50 - i * (BLOCK_SIZE + BLOCK_SPACING); // Top-down drawing

    if (bit) {
      display.fillRect(x_offset, y, BLOCK_SIZE, BLOCK_SIZE, SSD1306_WHITE);
    } else {
      display.drawRect(x_offset, y, BLOCK_SIZE, BLOCK_SIZE, SSD1306_WHITE);
    }
  }
}
