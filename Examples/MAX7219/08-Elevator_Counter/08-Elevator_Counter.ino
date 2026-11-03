//Elevator Counter
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define MAX_DEVICES 1 // Use the number of devices you have
#define CS_PIN 10
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int currentFloor = 0;
int direction = 1;  // 1 = up, -1 = down
char floorText[4];  // Enough to hold "5" or even "G", "10" etc.

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();

  sprintf(floorText, "%d", currentFloor);
  display.displayText(floorText, PA_CENTER, 100, 1000, PA_SCROLL_UP, PA_SCROLL_UP);
}

void loop() {
  if (display.displayAnimate()) {
    currentFloor += direction;

    if (currentFloor > 5) {
      currentFloor = 5;
      direction = -1;
    } else if (currentFloor < 0) {
      currentFloor = 0;
      direction = 1;
    }

    // Select direction of scroll
    textEffect_t scrollEffect = (direction == 1) ? PA_SCROLL_UP : PA_SCROLL_DOWN;

    // Prepare new text in persistent buffer
    sprintf(floorText, "%d", currentFloor);
    display.displayText(floorText, PA_CENTER, 100, 1000, scrollEffect, scrollEffect);
  }
}
