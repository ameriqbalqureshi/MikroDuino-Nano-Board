//Tetris Game
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 10

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

const int buttonLeft = 3;
const int buttonRight = 4;

bool grid[8][8] = {0};  // Display buffer
int blockX = 3;         // Horizontal position of falling block
int blockY = 0;         // Vertical position

unsigned long lastFall = 0;
const int fallInterval = 500; // Milliseconds

void setup() {
  mx.begin();
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonRight, INPUT_PULLUP);
  mx.clear();
  mx.update();
}

void loop() {
  // Input handling
  if (digitalRead(buttonLeft) == LOW && blockX > 0 && !grid[blockY][blockX - 1]) {
    blockX--;
    delay(150);
  }
  if (digitalRead(buttonRight) == LOW && blockX < 7 && !grid[blockY][blockX + 1]) {
    blockX++;
    delay(150);
  }

  // Time-based falling logic
  if (millis() - lastFall > fallInterval) {
    lastFall = millis();

    // Check if block can fall
    if (blockY < 7 && !grid[blockY + 1][blockX]) {
      blockY++;
    } else {
      // Fix block to grid
      grid[blockY][blockX] = true;

      // Check and clear full rows
      for (int y = 7; y >= 0; y--) {
        bool full = true;
        for (int x = 0; x < 8; x++) {
          if (!grid[y][x]) {
            full = false;
            break;
          }
        }
        if (full) {
          // Clear row and move above rows down
          for (int yy = y; yy > 0; yy--) {
            for (int xx = 0; xx < 8; xx++) {
              grid[yy][xx] = grid[yy - 1][xx];
            }
          }
          for (int xx = 0; xx < 8; xx++) grid[0][xx] = false;
          y++;  // Recheck same row
        }
      }

      // Spawn new block
      blockX = 3;
      blockY = 0;

      // Game Over condition
      if (grid[blockY][blockX]) {
        for (int y = 0; y < 8; y++)
          for (int x = 0; x < 8; x++)
            grid[y][x] = false;
        delay(1000);  // Pause
      }
    }
  }

  // Draw frame
  mx.clear();
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      mx.setPoint(y, x, grid[y][x]);
    }
  }
  mx.setPoint(blockY, blockX, true);  // Draw falling block
  mx.update();
}
