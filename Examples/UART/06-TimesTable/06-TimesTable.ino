// Read a number and produce a times table
void setup() {
    Serial.begin(9600);  // Initialize Serial Communication
    Serial.println("Enter a number between 2 and 16 to get its times table:");
}

void loop() {
    if (Serial.available()) {
        int num = Serial.parseInt();  // Read the integer input

        // Validate the number range
        if (num >= 2 && num <= 16) {
            Serial.print("Times table for ");
            Serial.println(num);
            
            for (int i = 1; i <= 10; i++) {
                Serial.print(num);
                Serial.print(" x ");
                Serial.print(i);
                Serial.print(" = ");
                Serial.println(num * i);
            }
        } 
        else {
            Serial.println("Invalid input! Please enter a number between 2 and 16.");
        }
        
        Serial.println("Enter another number:");
        delay(500);  // Short delay to prevent repeated reads
    }
}
