#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Configuration
#define NUM_BARS 16
int barWidth = SCREEN_WIDTH / NUM_BARS;
int barHeights[NUM_BARS];

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  randomSeed(analogRead(0));  // Seed for random values
  display.clearDisplay();
  display.display();
}

void loop() {
  // Generate simulated data (random heights)
  for (int i = 0; i < NUM_BARS; i++) {
    barHeights[i] = random(5, SCREEN_HEIGHT - 5);  // simulate amplitude
  }

  // Clear display
  display.clearDisplay();

  // Draw bars
  for (int i = 0; i < NUM_BARS; i++) {
    int x = i * barWidth;
    int y = SCREEN_HEIGHT - barHeights[i];
    display.fillRect(x + 1, y, barWidth - 2, barHeights[i], SSD1306_WHITE);
  }

  display.display();
  delay(100);  // adjust for animation speed
}
