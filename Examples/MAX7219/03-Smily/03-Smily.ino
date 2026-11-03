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
mx.control(MD_MAX72XX::INTENSITY, 5);

}

uint8_t smiley[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

void loop() {
  mx.clear();
  for (uint8_t row = 0; row < 8; row++) {
    mx.setRow(0, row, smiley[row]);
  }
  delay(2000);
}


