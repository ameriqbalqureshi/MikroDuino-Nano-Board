//Dodging Game
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDR 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button pins
#define LEFT_BUTTON 3
#define RIGHT_BUTTON 4

// Player variables
#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 4
int playerX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
const int playerY = SCREEN_HEIGHT - PLAYER_HEIGHT;

// Obstacle variables
int obstacleX;
int obstacleY = 0;
const int obstacleSize = 8;
int obstacleSpeed = 2;

bool gameOver = false;

void spawnObstacle() {
  obstacleX = random(0, SCREEN_WIDTH - obstacleSize);
  obstacleY = 0;
}

void setup() {
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(0));
  spawnObstacle();
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(30, 30);
    display.print("Game Over!");
    display.display();
    delay(3000);
    // Restart game
    playerX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
    gameOver = false;
    spawnObstacle();
  }

  // Handle input
  if (digitalRead(LEFT_BUTTON) == LOW && playerX > 0) {
    playerX -= 3;
  }
  if (digitalRead(RIGHT_BUTTON) == LOW && playerX < SCREEN_WIDTH - PLAYER_WIDTH) {
    playerX += 3;
  }

  // Move obstacle
  obstacleY += obstacleSpeed;

  // Check collision
  if (obstacleY + obstacleSize >= playerY &&
      obstacleX + obstacleSize > playerX &&
      obstacleX < playerX + PLAYER_WIDTH) {
    gameOver = true;
  }

  // Respawn obstacle if it goes off screen
  if (obstacleY > SCREEN_HEIGHT) {
    spawnObstacle();
  }

  // Draw everything
  display.clearDisplay();

  // Draw player
  display.fillRect(playerX, playerY, PLAYER_WIDTH, PLAYER_HEIGHT, SSD1306_WHITE);

  // Draw obstacle
  display.fillRect(obstacleX, obstacleY, obstacleSize, obstacleSize, SSD1306_WHITE);

  display.display();
  delay(50); // controls game speed
}
