#include <Wire.h>
#include <RTClib.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
RTC_DS1307 rtc;

void setup() {
  Wire.begin();
  rtc.begin();
  mx.begin();
  mx.clear();
  mx.update();

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set RTC to compile time
  }
}

void loop() {
  DateTime now = rtc.now();

  mx.clear();

  // Display time in binary (HOURS on rows 0–1, MINUTES on 2–3, SECONDS on 4–5)
  drawBinary(now.hour(), 0);
  drawBinary(now.minute(), 2);
  drawBinary(now.second(), 4);

  mx.update();
  delay(500);
}

// Draw binary with MSB on LEFT (col 0) and LSB on RIGHT (col 5)
void drawBinary(uint8_t value, uint8_t startRow) {
  for (uint8_t i = 0; i < 6; i++) {  // 6 bits max
    bool bit = bitRead(value, 5 - i);   // bit 5 is MSB, bit 0 is LSB
    uint8_t col = i;                   // MSB → col 0, LSB → col 5
    mx.setPoint(startRow, col, bit);
    mx.setPoint(startRow + 1, col, bit);  // for visibility (2-row thickness)
  }
}
