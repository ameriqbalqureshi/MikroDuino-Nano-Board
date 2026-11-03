// DHT11 OLED, Bargraph
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define DHTPIN A1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  display.clearDisplay();

  if (isnan(h) || isnan(t)) {
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Sensor Error");
    display.display();
    delay(2000);
    return;
  }

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp: "); display.print(t); display.println(" C");
  display.print("Hum:  "); display.print(h); display.println(" %");

  // Draw humidity bar
  display.drawRect(0, 30, 100, 10, SSD1306_WHITE); // Outline
  display.fillRect(1, 31, map(h, 0, 100, 0, 98), 8, SSD1306_WHITE); // Fill based on % humidity

  display.display();
  delay(2000);
}
