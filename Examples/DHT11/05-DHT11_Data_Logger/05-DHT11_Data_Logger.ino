//DHT11 Full data logger
// Stores data in I2C EEPROM
#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

#define DHTPIN A1
#define DHTTYPE DHT11
#define BUTTON_PIN 2

#define EEPROM_ADDR 0x50 // I2C address of AT24C32 or AT24C256
#define RECORD_SIZE 7    // 1 byte hour + 1 min + 1 sec + 2 temp + 2 hum

RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);

unsigned int eepromAddr = 0; // EEPROM write pointer

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
  rtc.begin();

  pinMode(BUTTON_PIN, INPUT);

  if (!rtc.isrunning()) {
    Serial.println("RTC not running. Setting default time.");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Set to compile time
  }

  Serial.println("System ready: Logging every 10 sec...");
}

void loop() {
  static unsigned long lastLog = 0;

  if (millis() - lastLog >= 10000 && eepromAddr < 0x7FFF - RECORD_SIZE) {
    DateTime now = rtc.now();
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    if (!isnan(t) && !isnan(h)) {
      writeLogRecord(now, t, h);
      Serial.print("Logged at ");
      Serial.print(now.timestamp(DateTime::TIMESTAMP_TIME));
      Serial.print(" - T: ");
      Serial.print(t);
      Serial.print(" C, H: ");
      Serial.print(h);
      Serial.println(" %");
    }

    lastLog = millis();
  }

  // Display on plotter
  if (digitalRead(BUTTON_PIN) == HIGH) {
    Serial.println("Plotting data to Serial Plotter...");
    plotData();
    delay(1000); // debounce
  }
}

void writeLogRecord(DateTime now, float temp, float hum) {
  Wire.beginTransmission(EEPROM_ADDR);
  Wire.write((int)(eepromAddr >> 8));     // high byte
  Wire.write((int)(eepromAddr & 0xFF));   // low byte
  Wire.write(now.hour());
  Wire.write(now.minute());
  Wire.write(now.second());

  int t = temp * 100;
  int h = hum * 100;

  Wire.write(highByte(t));
  Wire.write(lowByte(t));
  Wire.write(highByte(h));
  Wire.write(lowByte(h));
  Wire.endTransmission();

  eepromAddr += RECORD_SIZE;
  delay(5); // EEPROM write delay
}

void plotData() {
  unsigned int addr = 0;

  while (addr < eepromAddr) {
    Wire.beginTransmission(EEPROM_ADDR);
    Wire.write(addr >> 8);
    Wire.write(addr & 0xFF);
    Wire.endTransmission();

    Wire.requestFrom(EEPROM_ADDR, RECORD_SIZE);
    if (Wire.available() >= RECORD_SIZE) {
      byte hr = Wire.read();
      byte mn = Wire.read();
      byte sc = Wire.read();
      int t = (Wire.read() << 8) | Wire.read();
      int h = (Wire.read() << 8) | Wire.read();

      float temp = t / 100.0;
      float hum = h / 100.0;

      // Output for serial plotter (2 lines)
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(", Humidity: ");
      Serial.println(hum);
    }
    addr += RECORD_SIZE;
    delay(10); // allow time for plotter to catch up
  }
}
