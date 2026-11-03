// MPU6050 with OLED
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

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Initialize MPU6050
  if (!mpu.begin()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("MPU6050 not found");
    display.display();
    while (true);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("MPU6050 Ready!");
  display.display();
  delay(1000);
}

void loop() {
  sensors_event_t accel, gyro, temp;
  mpu.getEvent(&accel, &gyro, &temp);

  // Clear display buffer
  display.clearDisplay();
  display.setCursor(0, 0);
  
  // Display acceleration
  display.println("Accel (m/s^2):");
  display.print("X: "); display.println(accel.acceleration.x, 1);
  display.print("Y: "); display.println(accel.acceleration.y, 1);
  display.print("Z: "); display.println(accel.acceleration.z, 1);
  
  // Display temperature
  display.print("Temp: "); display.print(temp.temperature, 1);
  display.println(" C");

  // Show buffer on screen
  display.display();
  delay(500);
}
