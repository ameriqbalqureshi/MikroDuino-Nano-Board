//DHT11 data logger store data in EEPROM Display on terminal when Button D2 is pressed
#include <EEPROM.h>
#include <DHT.h>

#define DHTPIN A1
#define DHTTYPE DHT11
#define BUTTON_PIN 2

DHT dht(DHTPIN, DHTTYPE);

// Each entry will take 4 bytes: 2 for temperature, 2 for humidity (float values stored as int * 100)
const int RECORD_SIZE = 4;
const int MAX_RECORDS = 100; // EEPROM on Nano has 1024 bytes. 100 records = 400 bytes max.
int recordIndex = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(BUTTON_PIN, INPUT);
  Serial.println("EEPROM Data Logger Ready");
}

void loop() {
  static unsigned long lastLogTime = 0;

  // Log data every 10 seconds
  if (millis() - lastLogTime > 10000 && recordIndex < MAX_RECORDS) {
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    if (!isnan(temp) && !isnan(hum)) {
      saveToEEPROM(recordIndex, temp, hum);
      Serial.print("Saved Record #");
      Serial.print(recordIndex);
      Serial.print(" -> Temp: ");
      Serial.print(temp);
      Serial.print(" C, Humidity: ");
      Serial.print(hum);
      Serial.println(" %");

      recordIndex++;
    } else {
      Serial.println("Sensor error, skipping logging.");
    }

    lastLogTime = millis();
  }

  // If button pressed, print stored data
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("\n--- EEPROM Logged Data ---");
    for (int i = 0; i < recordIndex; i++) {
      float temp, hum;
      readFromEEPROM(i, temp, hum);
      Serial.print("Record ");
      Serial.print(i);
      Serial.print(": Temp = ");
      Serial.print(temp);
      Serial.print(" C, Humidity = ");
      Serial.print(hum);
      Serial.println(" %");
    }
    Serial.println("---------------------------\n");
    delay(1000); // debounce and avoid repeat reads
  }
}

// Save a reading to EEPROM at given index
void saveToEEPROM(int index, float temp, float hum) {
  int addr = index * RECORD_SIZE;
  int t = int(temp * 100);
  int h = int(hum * 100);

  EEPROM.put(addr, t);
  EEPROM.put(addr + 2, h);
}

// Read a reading from EEPROM
void readFromEEPROM(int index, float &temp, float &hum) {
  int addr = index * RECORD_SIZE;
  int t, h;
  EEPROM.get(addr, t);
  EEPROM.get(addr + 2, h);

  temp = t / 100.0;
  hum = h / 100.0;
}
