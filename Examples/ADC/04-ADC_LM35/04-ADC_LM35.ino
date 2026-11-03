// LM35 Temperature demo
#define TEMP_SENSOR A0

void setup() {
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(TEMP_SENSOR);
    float temperature = sensorValue * (5.0 / 1023.0) * 100; // Convert to °C
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    delay(1000);
}
