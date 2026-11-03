//Displaying Single Character
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  matrix.begin();
  matrix.control(MD_MAX72XX::INTENSITY, 5);
  matrix.clear();
  matrix.setChar(6  , 'A');
}

void loop() {
  // Do nothing, static display
}
