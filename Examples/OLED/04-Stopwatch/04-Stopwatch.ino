//Simple stopwatch 
//S3 to start and stop
//S4 to reset
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define BUTTON_START 3
#define BUTTON_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool running = false;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

bool lastStartState = HIGH;
bool lastResetState = HIGH;

char timeString[16];  // Buffer for formatted time

void setup() {
  pinMode(BUTTON_START, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(2);
  updateDisplay();
}

void loop() {
  // Handle start/stop button
  bool currentStartState = digitalRead(BUTTON_START);
  if (currentStartState == LOW && lastStartState == HIGH) {
    running = !running;
    if (running) {
      startTime = millis() - elapsedTime;
    } else {
      elapsedTime = millis() - startTime;
    }
    delay(200);  // Debounce delay
  }
  lastStartState = currentStartState;

  // Handle reset button
  bool currentResetState = digitalRead(BUTTON_RESET);
  if (currentResetState == LOW && lastResetState == HIGH) {
    running = false;
    elapsedTime = 0;
    updateDisplay();
    delay(200);  // Debounce delay
  }
  lastResetState = currentResetState;

  // Update elapsed time
  if (running) {
    elapsedTime = millis() - startTime;
  }

  updateDisplay();
  delay(50);  // Smooth refresh rate
}

void updateDisplay() {
  unsigned long centi = (elapsedTime / 10) % 100;
  unsigned long seconds = (elapsedTime / 1000) % 60;
  unsigned long minutes = (elapsedTime / 60000);

  sprintf(timeString, "%02lu:%02lu.%02lu", minutes, seconds, centi);

  display.clearDisplay();
  display.setCursor(10, 20);
  display.print(timeString);
  display.display();
}
