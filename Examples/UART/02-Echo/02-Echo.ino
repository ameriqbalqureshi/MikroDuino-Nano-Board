// Echo Back The received character
void setup() {
    Serial.begin(9600); // Start serial communication
}

void loop() {
    if (Serial.available()) { // Check if data is available
        char receivedChar = Serial.read(); // Read the received character
        Serial.print("You sent: ");
        Serial.println(receivedChar); // Echo back the received character
    }
}
