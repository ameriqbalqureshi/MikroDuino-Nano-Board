void setup() {
    Serial.begin(9600); // Start serial communication at 9600 baud
}

void loop() {
    Serial.println("Hello, Arduino!"); // Send data to Serial Monitor
    delay(1000); // Wait for 1 second
}
