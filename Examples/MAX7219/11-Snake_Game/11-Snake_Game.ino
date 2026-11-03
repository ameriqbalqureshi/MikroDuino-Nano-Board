//snake game
// use Buttons to navigate
#include <MD_MAX72xx.h>
#include <SPI.h>

#define MAX_DEVICES 1
#define CS_PIN 10
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

#define UP_PIN 2
#define DOWN_PIN 3
#define LEFT_PIN 4
#define RIGHT_PIN 5

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

#define SNAKE_MAX 64
int snakeX[SNAKE_MAX];
int snakeY[SNAKE_MAX];
int snakeLength = 3;

int dx = 1;  // initial direction: right
int dy = 0;

int foodX, foodY;

void generateFood() {
  bool valid;
  do {
    valid = true;
    foodX = random(0, 8);
    foodY = random(0, 8);
    for (int i = 0; i < snakeLength; i++) {
      if (snakeX[i] == foodX && snakeY[i] == foodY) {
        valid = false;
        break;
      }
    }
  } while (!valid);
}

void readInput() {
  if (digitalRead(UP_PIN) == LOW && dy != 1) {
    dx = 0; dy = -1;
  } else if (digitalRead(DOWN_PIN) == LOW && dy != -1) {
    dx = 0; dy = 1;
  } else if (digitalRead(LEFT_PIN) == LOW && dx != 1) {
    dx = -1; dy = 0;
  } else if (digitalRead(RIGHT_PIN) == LOW && dx != -1) {
    dx = 1; dy = 0;
  }
}

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 3);
  mx.clear();

  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);

  snakeX[0] = 2; snakeY[0] = 3;
  snakeX[1] = 1; snakeY[1] = 3;
  snakeX[2] = 0; snakeY[2] = 3;

  generateFood();
}

void loop() {
  readInput();

  // Move snake
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  snakeX[0] += dx;
  snakeY[0] += dy;

  // Check wall collision
  if (snakeX[0] < 0 || snakeX[0] > 7 || snakeY[0] < 0 || snakeY[0] > 7) {
    // Game over
    while (true) {
      mx.clear();
      mx.setChar(0, 'X'); // Show X for crash
      delay(500);
    }
  }

  // Check self collision
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      while (true) {
        mx.clear();
        mx.setChar(0, 'X');
        delay(500);
      }
    }
  }

  // Check food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (snakeLength < SNAKE_MAX) snakeLength++;
    generateFood();
  }

  // Draw everything
  mx.clear();
  for (int i = 0; i < snakeLength; i++) {
    mx.setPoint(snakeY[i], snakeX[i], true);
  }
  mx.setPoint(foodY, foodX, true);

  delay(300);
}
