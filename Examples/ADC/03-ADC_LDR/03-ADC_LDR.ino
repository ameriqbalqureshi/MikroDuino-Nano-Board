// LDR Demo
#define LDR_PIN A6
#define LED_PIN 6

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    int lightValue = analogRead(LDR_PIN);
    Serial.println(lightValue); 

    if (lightValue < 500) { // Adjust threshold as needed
        digitalWrite(LED_PIN, HIGH); // Turn ON LED
    } else {
        digitalWrite(LED_PIN, LOW);  // Turn OFF LED
    }

    delay(500);
}
