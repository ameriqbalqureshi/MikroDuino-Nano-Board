//Scrolling text
// Use cascaded 4 modules
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define MAX_DEVICES 1  // change the number of modules you are using
#define CS_PIN 10
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();
  display.displayText("WELCOME", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  display.displayAnimate();
}

void loop() {
  if (display.displayAnimate()) {
    display.displayReset();
  }
}
