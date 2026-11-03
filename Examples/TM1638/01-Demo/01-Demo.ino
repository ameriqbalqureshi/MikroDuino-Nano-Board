#include <TM1638.h>

#define DIO 8
#define CLK 9
#define STB 7

TM1638 module(DIO, CLK, STB);

void setup() {
  // Show a welcome message on the segments
  module.setDisplayToString("HELLO");

  delay(2000);

  // Display a number
  module.setDisplayToDecNumber(12345678, 0, false);

  // Turn on LEDs one by one
  for (int i = 0; i < 8; i++) {
    module.setLED(TM1638_COLOR_RED, i); // Red LED on at position i
    delay(200);
  }
}

void loop() {
  // Read buttons and reflect their state on LEDs
  byte buttons = module.getButtons();

  for (int i = 0; i < 8; i++) {
    bool pressed = buttons & (1 << i);
    module.setLED(pressed ? TM1638_COLOR_RED : TM1638_COLOR_NONE, i);
  }

  // Display the value of pressed buttons (as binary pattern)
  module.setDisplayToDecNumber(buttons, 0, false);
  delay(200);
}
