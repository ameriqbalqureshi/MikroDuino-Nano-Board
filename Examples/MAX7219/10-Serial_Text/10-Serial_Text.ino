//Display text, transmitted by serial terminal
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1         // Number of 8x8 modules
#define CS_PIN 10             // Chip Select for SPI

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

String inputText = "";

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setIntensity(5);      // Brightness: 0–15
  display.displayClear();
  display.displayScroll("Send Text via Serial", PA_LEFT, PA_SCROLL_LEFT, 50);
  display.displayAnimate();
}

void loop() {
  if (Serial.available()) {
    inputText = Serial.readStringUntil('\n');
    inputText.trim();   // Remove trailing newline or spaces

    if (inputText.length() > 0) {
      display.displayClear();
      display.displayScroll(inputText.c_str(), PA_LEFT, PA_SCROLL_LEFT, 50);
    }
  }

  if (display.displayAnimate()) {
    // Automatically restart animation
    display.displayReset();
  }
}
