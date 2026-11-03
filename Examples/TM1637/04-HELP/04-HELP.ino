#include <TM1637Display.h>

#define CLK 12
#define DIO 11

TM1637Display display(CLK, DIO);

// Define segment bitmaps for H, E, L, P
const uint8_t HELP[] = {
  SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,         // E
  SEG_D | SEG_E | SEG_F,                         // L
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G          // P
};

void setup() {
  display.setBrightness(7);           // Max brightness
  display.setSegments(HELP);          // Display HELP
}

void loop() {
  // Nothing in loop, static display
}
