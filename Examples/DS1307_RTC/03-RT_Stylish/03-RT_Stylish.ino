// A little stylish and professional looking RTC on OLED
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

bool showColon = true; // Flag for blinking colon

void setup() {
  Wire.begin();
  rtc.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(__DATE__, __TIME__)); // Set RTC to compile time (optional)
  }
}

void loop() {
  DateTime now = rtc.now();

  display.clearDisplay();

  // ---- Draw Time ----
  display.setTextSize(3);
  
  // Centering the time (approximation for OLED 128x64)
  int xCenter = 10;
  int yCenter = 10;
  display.setCursor(xCenter, yCenter);

  // Print Hours
  if (now.hour() < 10) display.print('0');
  display.print(now.hour());

  // Print Blinking Colon
  if (showColon) {
    display.print(':');
  } else {
    display.print(' ');
  }

  // Print Minutes
  if (now.minute() < 10) display.print('0');
  display.print(now.minute());

  // ---- Draw Date below ----
  display.setTextSize(1);
  display.setCursor(20, 50);
  if (now.day() < 10) display.print('0');
  display.print(now.day());
  display.print('/');
  if (now.month() < 10) display.print('0');
  display.print(now.month());
  display.print('/');
  display.print(now.year());

  display.display();

  // Toggle colon every second
  showColon = !showColon;
  
  delay(1000); // Update every second
}
