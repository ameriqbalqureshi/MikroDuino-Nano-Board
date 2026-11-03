//Draw a diagonal Line
#include <MD_MAX72xx.h>
#include <SPI.h>

// MAX7219 8x8 LED Matrix
// Define hardware type and SPI pins
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  mx.begin();
  mx.clear();
}

void loop() {
  mx.clear();
  for (uint8_t i = 0; i < 8; i++) {
    mx.setPoint(i, i, true);  // draw diagonal
    delay(100);
  }
  delay(1000);
}

