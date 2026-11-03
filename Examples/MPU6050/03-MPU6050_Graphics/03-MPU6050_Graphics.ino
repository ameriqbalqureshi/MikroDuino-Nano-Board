//MPU6050 OLED Graphics
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  if (!mpu.begin()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("MPU6050 not found");
    display.display();
    while (true);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  display.clearDisplay();
  display.display();
  delay(1000);
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  display.clearDisplay();

  // Draw X bar
  drawAxisBar(0, "X", a.acceleration.x);

  // Draw Y bar
  drawAxisBar(22, "Y", a.acceleration.y);

  // Draw Z bar
  drawAxisBar(44, "Z", a.acceleration.z);

  display.display();
  delay(200);
}

void drawAxisBar(int y, const char* label, float value) {
  int centerX = SCREEN_WIDTH / 2;
  int barLength = map(constrain(value * 10, -80, 80), -80, 80, -50, 50); // ±8 m/s² → ±50 pixels

  display.setCursor(0, y);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(label);
  display.print(":");

  // Draw central baseline
  display.drawLine(centerX, y + 10, centerX, y + 14, SSD1306_WHITE);

  // Draw bar to the right or left of center
  if (barLength >= 0) {
    display.fillRect(centerX + 1, y + 10, barLength, 4, SSD1306_WHITE);
  } else {
    display.fillRect(centerX + barLength, y + 10, -barLength, 4, SSD1306_WHITE);
  }
}
