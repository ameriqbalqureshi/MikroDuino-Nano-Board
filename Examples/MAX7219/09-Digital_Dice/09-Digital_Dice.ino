// Digital dice
// Use D2 Button to scroll
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10
#define BUTTON_PIN 2

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

int currentDice = 1;
bool lastButtonState = HIGH;

byte dicePatterns[6][8] = {
  // Dice 1
  {
    B00000000,
    B00000000,
    B00000000,
    B00010000,
    B00010000,
    B00000000,
    B00000000,
    B00000000
  },
  // Dice 2
  {
    B00000000,
    B00000000,
    B00000010,
    B00000000,
    B00000000,
    B01000000,
    B00000000,
    B00000000
  },
  // Dice 3
  {
    B00000000,
    B00000010,
    B00000000,
    B00010000,
    B00000000,
    B01000000,
    B00000000,
    B00000000
  },
  // Dice 4
  {
    B00000000,
    B01000010,
    B00000000,
    B00000000,
    B00000000,
    B01000010,
    B00000000,
    B00000000
  },
  // Dice 5
  {
    B00000000,
    B01000010,
    B00000000,
    B00010000,
    B00000000,
    B01000010,
    B00000000,
    B00000000
  },
  // Dice 6
  {
    B00000000,
    B01000010,
    B00000000,
    B01000010,
    B00000000,
    B01000010,
    B00000000,
    B00000000
  }
};

void setup() {
  mx.begin();
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // use internal pull-up
  displayDice(currentDice);
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  // Detect button press (falling edge)
  if (lastButtonState == HIGH && buttonState == LOW) {
    rollDice();
  }

  lastButtonState = buttonState;
}

void rollDice() {
  // Simulate roll animation
  for (int i = 0; i < 10; i++) {
    int r = random(1, 7);
    displayDice(r);
    delay(100);
  }

  // Set final number
  currentDice = random(1, 7);
  displayDice(currentDice);
}

void displayDice(int number) {
  mx.clear();
  for (int row = 0; row < 8; row++) {
    mx.setRow(0, row, dicePatterns[number - 1][row]);
  }
}
