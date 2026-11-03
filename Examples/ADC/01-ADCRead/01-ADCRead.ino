// Read Analog data from potentiometer
// display raw ADC value of serial monitor
#define POT_PIN A7
void setup() {
    Serial.begin(9600); // Start serial communication
}

void loop() {
    int sensorValue = analogRead(POT_PIN); // Read the analog input (0-1023)
    Serial.println(sensorValue);      // Print the value to Serial Monitor
    delay(500); // Delay for readability
}
