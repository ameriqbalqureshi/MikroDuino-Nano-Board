#include <TM1637Display.h>

// Define connections (CLK and DIO)
#define CLK 12
#define DIO 11

// Create display object
TM1637Display display(CLK, DIO);

void setup() {
  // Set display brightness (0 to 7)
  display.setBrightness(5);  // Medium brightness

  // Display a number
  int value = 1234;
  display.showNumberDec(value);  // Display 1234 in decimal
}

void loop() {
  // Nothing to do here
}
