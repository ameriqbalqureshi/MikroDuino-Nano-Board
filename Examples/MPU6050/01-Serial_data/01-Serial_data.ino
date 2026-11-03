//MPU6050
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // Wait for Serial Monitor

  Serial.println("MPU6050 Sensor Test");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 connected!");

  // Optional: Configure settings
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t accel, gyro, temp;

  // Get fresh sensor readings
  mpu.getEvent(&accel, &gyro, &temp);

  // Print acceleration
  Serial.print("Accel (m/s^2): ");
  Serial.print(accel.acceleration.x); Serial.print(", ");
  Serial.print(accel.acceleration.y); Serial.print(", ");
  Serial.print(accel.acceleration.z);

  // Print gyroscope
  Serial.print(" | Gyro (rad/s): ");
  Serial.print(gyro.gyro.x); Serial.print(", ");
  Serial.print(gyro.gyro.y); Serial.print(", ");
  Serial.print(gyro.gyro.z);

  // Print temperature
  Serial.print(" | Temp (°C): ");
  Serial.println(temp.temperature);

  delay(500); // Delay for readability
}
