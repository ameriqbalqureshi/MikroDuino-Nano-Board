//Tic Tac Toe game
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

// Game state
char board[3][3];
int cursorX = 0;
int cursorY = 0;
char currentPlayer = 'X';
bool gameOver = false;

// Button timing
unsigned long lastPressTime = 0;

void drawGrid() {
  display.clearDisplay();

  // Draw vertical lines
  display.drawLine(42, 0, 42, 64, SSD1306_WHITE);
  display.drawLine(85, 0, 85, 64, SSD1306_WHITE);

  // Draw horizontal lines
  display.drawLine(0, 21, 128, 21, SSD1306_WHITE);
  display.drawLine(0, 43, 128, 43, SSD1306_WHITE);

  // Draw Xs and Os
  for (int y = 0; y < 3; y++) {
    for (int x = 0; x < 3; x++) {
      int cellX = x * 42 + 10;
      int cellY = y * 21 + 5;

      if (board[y][x] == 'X') {
        display.drawLine(cellX, cellY, cellX + 20, cellY + 15, SSD1306_WHITE);
        display.drawLine(cellX + 20, cellY, cellX, cellY + 15, SSD1306_WHITE);
      } else if (board[y][x] == 'O') {
        display.drawCircle(cellX + 10, cellY + 8, 8, SSD1306_WHITE);
      }
    }
  }

  // Draw cursor
  int cursorPixelX = cursorX * 42;
  int cursorPixelY = cursorY * 21;
  display.drawRect(cursorPixelX, cursorPixelY, 42, 21, SSD1306_WHITE);

  display.display();
}

bool isButtonPressed(int pin) {
  return digitalRead(pin) == LOW;
}

bool isCellEmpty(int x, int y) {
  return board[y][x] == ' ';
}

void markCell(int x, int y, char player) {
  board[y][x] = player;
}

char checkWinner() {
  for (int i = 0; i < 3; i++) {
    // Check rows and columns
    if (board[i][0] != ' ' &&
        board[i][0] == board[i][1] &&
        board[i][1] == board[i][2])
      return board[i][0];

    if (board[0][i] != ' ' &&
        board[0][i] == board[1][i] &&
        board[1][i] == board[2][i])
      return board[0][i];
  }

  // Diagonals
  if (board[0][0] != ' ' &&
      board[0][0] == board[1][1] &&
      board[1][1] == board[2][2])
    return board[0][0];

  if (board[0][2] != ' ' &&
      board[0][2] == board[1][1] &&
      board[1][1] == board[2][0])
    return board[0][2];

  return ' ';
}

bool isDraw() {
  for (int y = 0; y < 3; y++)
    for (int x = 0; x < 3; x++)
      if (board[y][x] == ' ') return false;
  return true;
}

void displayEnd(char winner) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 20);
  if (winner != ' ')
    display.print(String("Winner: ") + winner);
  else
    display.print("It's a draw!");
  display.display();
  delay(3000);
}

void resetGame() {
  for (int y = 0; y < 3; y++)
    for (int x = 0; x < 3; x++)
      board[y][x] = ' ';
  cursorX = 0;
  cursorY = 0;
  currentPlayer = 'X';
  gameOver = false;
  drawGrid();
}

void setup() {
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  resetGame();
}

void loop() {
  if (gameOver) {
    delay(1000);
    resetGame();
    return;
  }

  if (isButtonPressed(LEFT_BUTTON)) {
    if (cursorX > 0) cursorX--;
    delay(200);
  }

  if (isButtonPressed(RIGHT_BUTTON)) {
    if (cursorX < 2) cursorX++;
    delay(200);
  }

  if (isButtonPressed(UP_BUTTON)) {
    if (cursorY > 0) cursorY--;
    delay(200);
  }

  if (isButtonPressed(DOWN_BUTTON)) {
    if (cursorY < 2) cursorY++;
    delay(200);
  }

  // Long press any button to mark
  if (isCellEmpty(cursorX, cursorY)) {
    if (millis() - lastPressTime > 800 && (
        isButtonPressed(LEFT_BUTTON) ||
        isButtonPressed(RIGHT_BUTTON) ||
        isButtonPressed(UP_BUTTON) ||
        isButtonPressed(DOWN_BUTTON))) {
      
      markCell(cursorX, cursorY, currentPlayer);
      char winner = checkWinner();
      if (winner != ' ' || isDraw()) {
        displayEnd(winner);
        gameOver = true;
        return;
      }
      currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    } else if (
        isButtonPressed(LEFT_BUTTON) ||
        isButtonPressed(RIGHT_BUTTON) ||
        isButtonPressed(UP_BUTTON) ||
        isButtonPressed(DOWN_BUTTON)) {
      lastPressTime = millis();
    }
  }

  drawGrid();
}
