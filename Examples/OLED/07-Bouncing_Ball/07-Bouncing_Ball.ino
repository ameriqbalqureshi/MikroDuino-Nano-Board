#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin not used
#define OLED_ADDR 0x3C // I2C address

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Ball properties
int ballX = 10;
int ballY = 10;
int ballRadius = 4;
int dx = 2;
int dy = 1;

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  // Clear previous frame
  display.clearDisplay();

  // Draw the ball
  display.fillCircle(ballX, ballY, ballRadius, SSD1306_WHITE);

  // Display the ball
  display.display();

  // Update position
  ballX += dx;
  ballY += dy;

  // Check boundaries and reverse direction
  if (ballX - ballRadius <= 0 || ballX + ballRadius >= SCREEN_WIDTH) {
    dx = -dx;
  }
  if (ballY - ballRadius <= 0 || ballY + ballRadius >= SCREEN_HEIGHT) {
    dy = -dy;
  }

  delay(20); // Adjust speed
}
