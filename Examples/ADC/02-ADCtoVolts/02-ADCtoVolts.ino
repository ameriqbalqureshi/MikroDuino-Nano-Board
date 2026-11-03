// Read analog pin and convert ADC value to volts
#define POT_PIN A7 // POT pin on MikroDuino Board
void setup() {
    Serial.begin(9600);
}

void loop() {
    int sensorValue = analogRead(POT_PIN); // Read analog input
    float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage
    Serial.print("ADC Value:" );
    Serial.print(sensorValue);
    Serial.print(" Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
    delay(500);
}
