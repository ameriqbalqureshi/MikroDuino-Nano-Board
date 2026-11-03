//Snake Game on OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button pins
#define UP_BUTTON 2
#define LEFT_BUTTON 3
#define RIGHT_BUTTON 4
#define DOWN_BUTTON 5

// Snake variables
#define BLOCK_SIZE 4
#define MAX_LENGTH 64

int snakeX[MAX_LENGTH];
int snakeY[MAX_LENGTH];
int length = 3;
int dx = BLOCK_SIZE;
int dy = 0;

int foodX, foodY;
bool gameOver = false;

void spawnFood() {
  foodX = (random(SCREEN_WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
  foodY = (random(SCREEN_HEIGHT / BLOCK_SIZE)) * BLOCK_SIZE;
}

void setup() {
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(0));

  // Initialize snake position
  for (int i = 0; i < length; i++) {
    snakeX[i] = 40 - i * BLOCK_SIZE;
    snakeY[i] = 20;
  }

  spawnFood();
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 30);
    display.print("Game Over!");
    display.display();
    delay(2000);
    return;
  }

  // Handle input
  if (digitalRead(UP_BUTTON) == LOW && dy == 0) { dx = 0; dy = -BLOCK_SIZE; }
  if (digitalRead(DOWN_BUTTON) == LOW && dy == 0) { dx = 0; dy = BLOCK_SIZE; }
  if (digitalRead(LEFT_BUTTON) == LOW && dx == 0) { dx = -BLOCK_SIZE; dy = 0; }
  if (digitalRead(RIGHT_BUTTON) == LOW && dx == 0) { dx = BLOCK_SIZE; dy = 0; }

  // Move snake
  for (int i = length - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  snakeX[0] += dx;
  snakeY[0] += dy;

  // Check for collision with self or wall
  if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
    gameOver = true;
  }
  for (int i = 1; i < length; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameOver = true;
    }
  }

  // Check for eating food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    if (length < MAX_LENGTH) length++;
    spawnFood();
  }

  // Draw everything
  display.clearDisplay();

  // Draw snake
  for (int i = 0; i < length; i++) {
    display.fillRect(snakeX[i], snakeY[i], BLOCK_SIZE, BLOCK_SIZE, SSD1306_WHITE);
  }

  // Draw food
  display.fillRect(foodX, foodY, BLOCK_SIZE, BLOCK_SIZE, SSD1306_WHITE);

  display.display();
  delay(150); // Control speed
}
