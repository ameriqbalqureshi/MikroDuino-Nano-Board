//Pong game
// use buttons D3 and D4
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Button pins
const int buttonLeft = 4;
const int buttonRight = 3;

// Paddle position
int paddleX = 3;

// Ball position and direction
int ballX = 3, ballY = 6;
int ballDirX = 1; // +1 = right, -1 = left
int ballDirY = -1; // -1 = up, +1 = down

void setup() {
  mx.begin();
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  mx.clear();
  mx.update();
}

void loop() {
  mx.clear();

  // Read buttons
  if (digitalRead(buttonLeft) == LOW && paddleX > 0) {
    paddleX--;
  }
  if (digitalRead(buttonRight) == LOW && paddleX < 6) {
    paddleX++;
  }

  // Draw paddle (2 LEDs wide)
  mx.setPoint(7, paddleX, true);
  mx.setPoint(7, paddleX + 1, true);

  // Move ball
  ballX += ballDirX;
  ballY += ballDirY;

  // Bounce from left and right walls
  if (ballX < 0 || ballX > 7) {
    ballDirX = -ballDirX;
    ballX += ballDirX;
  }

  // Bounce from top wall
  if (ballY < 0) {
    ballDirY = -ballDirY;
    ballY += ballDirY;
  }

  // Check for collision with paddle
  if (ballY == 7) {
    if (ballX == paddleX || ballX == paddleX + 1) {
      ballDirY = -ballDirY;
      ballY += ballDirY;
    } else {
      // Missed! Reset game
      ballX = 3; ballY = 6;
      ballDirX = 1; ballDirY = -1;
      paddleX = 3;
    }
  }

  // Draw ball
  mx.setPoint(ballY, ballX, true);

  mx.update();
  delay(150); // adjust for speed
}
