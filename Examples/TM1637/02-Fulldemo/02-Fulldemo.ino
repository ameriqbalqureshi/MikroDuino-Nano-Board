#include <TM1637Display.h>

// Define TM1637 connection pins
#define CLK 12
#define DIO 11

// Create display object
TM1637Display display(CLK, DIO);

int counter = 0; // Number to display

void setup() {
  display.setBrightness(7);  // Max brightness

  // Display a welcome message briefly
  display.showNumberDec(8888);  // All segments on
  delay(1000);
  display.clear();
}

void loop() {
  // Show counting number
  display.showNumberDec(counter);

  // Wait 1 second
  delay(1000);

  counter++;

  // After 20 counts, show other display modes as a demo
  if (counter == 20) {
    display.clear();
    delay(1000);

    // Show number with leading zeros
    display.showNumberDec(42, true);  // Displays 0042
    delay(2000);

    // Show hexadecimal value (e.g., 0x1A3F)
    display.showNumberHexEx(0x1A3F);
    delay(2000);

    // Turn off display
    display.setBrightness(0, true); // Brightness 0, display off
    delay(1000);

    // Turn display back on
    display.setBrightness(7, true); // Brightness 7, display on
    delay(1000);

    
    delay(2000);
    display.clear();
    counter = 0;  // Reset counter
  }
}
