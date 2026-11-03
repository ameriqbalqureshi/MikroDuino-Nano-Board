//RTC clock on OLED
#include <Wire.h>                // For I2C communication
#include <RTClib.h>              // For DS1307 RTC
#include <Adafruit_GFX.h>        // Core graphics library
#include <Adafruit_SSD1306.h>    // OLED driver library

#define SCREEN_WIDTH 128         // OLED display width, in pixels
#define SCREEN_HEIGHT 64         // OLED display height, in pixels
#define OLED_RESET     -1        // Reset pin (not used with I2C)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS1307 rtc;                  // Create an RTC object

void setup() {
  Wire.begin();
  rtc.begin();

  // Initialize the OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // 0x3C is a common I2C address
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Optional: Adjust RTC once if needed
  // rtc.adjust(DateTime(2025, 4, 26, 15, 45, 0));  // Year, Month, Day, Hour, Minute, Second

  if (!rtc.isrunning()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("RTC not running!");
    display.display();
    while (1); // Halt if RTC not running
  }
}

void loop() {
  DateTime now = rtc.now(); // Read current time

  display.clearDisplay();
  
  display.setCursor(0, 10);
  display.setTextSize(2);   // Make text bigger for time display
  display.print(now.hour());
  display.print(':');
  if (now.minute() < 10) display.print('0'); // Leading zero for minute
  display.print(now.minute());
  display.print(':');
  if (now.second() < 10) display.print('0'); // Leading zero for second
  display.print(now.second());

  display.setTextSize(1);   // Smaller text for date
  display.setCursor(0, 40);
  display.print(now.day());
  display.print('/');
  display.print(now.month());
  display.print('/');
  display.print(now.year());

  display.display(); // Update the OLED screen
  delay(1000);       // Update every second
}
