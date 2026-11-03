// Echo Back The capital of received character
void setup() {
    Serial.begin(9600); // Start serial communication
}

void loop() {
    if (Serial.available()) { // Check if data is available
        char receivedChar = Serial.read(); // Read the received character
        Serial.print("You sent: ");
        if(receivedChar >= 'a' && receivedChar <='z')
          {
            receivedChar-=32; // Difference between 'a' and 'A'
          }
        Serial.println(receivedChar); // Echo back the received character
    }
}
