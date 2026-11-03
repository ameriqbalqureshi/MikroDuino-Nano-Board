#include <TM1637Display.h>

#define CLK 12
#define DIO 11

TM1637Display display(CLK, DIO);

const uint8_t LETTERS[][4] = {
  // H E L L
  {
    SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,         // H
    SEG_E | SEG_F | SEG_G,                         // E
    SEG_D | SEG_E | SEG_F,                         // L
    SEG_D | SEG_E | SEG_F                          // L
  },
  
};

void setup() {
  display.setBrightness(7);
}

void loop() {
  // Scroll HELLO by showing 4 characters at a time
  for (int i = 0; i < 2; i++) {
    display.setSegments(LETTERS[i], 4, 0);
    delay(600);
  }

  delay(2000); // Pause at the end
}
