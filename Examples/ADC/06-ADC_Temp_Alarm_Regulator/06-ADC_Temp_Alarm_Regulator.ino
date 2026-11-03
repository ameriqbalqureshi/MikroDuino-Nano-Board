// Temperature Alarm and Regulator system
// Receives a temperature limit (between 30°C and 50°C) from the serial terminal.
// Reads temperature from the LM35 sensor.
// Activates the fan (D6) and buzzer (A3) when the temperature exceeds the set limit.
// Turns off the fan and buzzer when the temperature drops 2°C below the set limit.


#define TEMP_SENSOR A0  // LM35 sensor connected to A0
#define FAN_PIN 6       // Fan connected to D6
#define BUZZER_PIN A3   // Buzzer connected to A3

int tempLimit = 35;     // Default temperature limit
int tempHysteresis;     // Temperature at which fan/buzzer turn off

void setup() {
    Serial.begin(9600);  
    pinMode(FAN_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    Serial.println("Enter Temperature Limit (30-50°C): ");
}

void loop() {
    if (Serial.available() > 0) { 
        int inputTemp = Serial.parseInt(); // Read integer input
        
        if (inputTemp >= 30 && inputTemp <= 50) { 
            tempLimit = inputTemp; 
            tempHysteresis = tempLimit - 2; // Fan and buzzer turn off 2°C below limit
            Serial.print("Set Temperature Limit: ");
            Serial.print(tempLimit);
            Serial.println("°C");
        } else {
            Serial.println("Invalid input! Enter a value between 30-50.");
        }
    }

    int tempValue = analogRead(TEMP_SENSOR); // Read LM35
    float temperature = (tempValue * 5.0 / 1023.0) * 100.0; // Convert to Celsius

    Serial.print("Current Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    if (temperature >= tempLimit) {
        digitalWrite(FAN_PIN, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
        Serial.println("ALARM! Fan and Buzzer ON");
    } else if (temperature <= tempHysteresis) {
        digitalWrite(FAN_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        Serial.println("Temperature Normal. Fan and Buzzer OFF");
    }

    delay(1000); // Update every second
}
