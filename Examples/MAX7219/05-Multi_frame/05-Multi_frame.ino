//Draw Multiple Frames
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
  mx.control(MD_MAX72XX::INTENSITY, 5);
}

uint8_t frames[2][8] = {
  {
    B00011000,
    B00111100,
    B01111110,
    B11111111,
    B11111111,
    B01111110,
    B00111100,
    B00011000
  },
  {
    B00000000,
    B00011000,
    B00111100,
    B01111110,
    B00111100,
    B00011000,
    B00000000,
    B00000000
  }
};

void loop() {
  for (uint8_t f = 0; f < 2; f++) {
    for (uint8_t row = 0; row < 8; row++) {
      mx.setRow(0, row, frames[f][row]);
    }
    delay(500);
  }
}
