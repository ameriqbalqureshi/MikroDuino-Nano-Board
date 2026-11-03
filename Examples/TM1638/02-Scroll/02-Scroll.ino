#include <TM1638.h>

#define DIO 8
#define CLK 9
#define STB 7

TM1638 module(DIO, CLK, STB);

const char* message = " ARDUINO OK ";  // Add spaces for clean scrolling
int position = 0;

void setup() {
  // Nothing needed here
}

void loop() {
  // Display 8 characters starting from position
  module.setDisplayToString(message + position);

  // Wait before next scroll step
  delay(300);

  // Move to next character in string
  position++;

  // If end of message is reached, restart
  if (position > strlen(message) - 8) {
    position = 0;
  }
}
