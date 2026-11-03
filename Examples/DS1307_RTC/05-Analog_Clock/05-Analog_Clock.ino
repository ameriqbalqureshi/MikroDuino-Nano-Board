// Analog clock
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define CLOCK_CENTER_X 64
#define CLOCK_CENTER_Y 32
#define CLOCK_RADIUS   30

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

void setup() {
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1); // loop forever
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  DateTime now = rtc.now();

  display.clearDisplay();
  drawClockFace();
  drawHands(now.hour(), now.minute(), now.second());
  display.display();
  
  delay(500); // refresh every half second
}

void drawClockFace() {
  // Draw outer circle
  display.drawCircle(CLOCK_CENTER_X, CLOCK_CENTER_Y, CLOCK_RADIUS, SSD1306_WHITE);

  // Draw 12 hour marks
  for (int i = 0; i < 12; i++) {
    float angle = i * 30 * PI / 180;
    int x1 = CLOCK_CENTER_X + (CLOCK_RADIUS - 2) * sin(angle);
    int y1 = CLOCK_CENTER_Y - (CLOCK_RADIUS - 2) * cos(angle);
    int x2 = CLOCK_CENTER_X + CLOCK_RADIUS * sin(angle);
    int y2 = CLOCK_CENTER_Y - CLOCK_RADIUS * cos(angle);
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }
}

void drawHands(int hour, int minute, int second) {
  float hour_angle = ((hour % 12) + minute / 60.0) * 30 * PI / 180;
  float minute_angle = (minute + second / 60.0) * 6 * PI / 180;
  float second_angle = second * 6 * PI / 180;

  // Hour hand
  drawHand(hour_angle, CLOCK_RADIUS * 0.5, 3);

  // Minute hand
  drawHand(minute_angle, CLOCK_RADIUS * 0.75, 2);

  // Second hand
  drawHand(second_angle, CLOCK_RADIUS * 0.9, 1);
}

void drawHand(float angle, float length, int thickness) {
  int x = CLOCK_CENTER_X + length * sin(angle);
  int y = CLOCK_CENTER_Y - length * cos(angle);

  if (thickness == 1) {
    display.drawLine(CLOCK_CENTER_X, CLOCK_CENTER_Y, x, y, SSD1306_WHITE);
  } else {
    for (int i = -thickness/2; i <= thickness/2; i++) {
      display.drawLine(CLOCK_CENTER_X+i, CLOCK_CENTER_Y+i, x+i, y+i, SSD1306_WHITE);
    }
  }
}
