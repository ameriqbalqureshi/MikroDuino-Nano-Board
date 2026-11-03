// Read a number from serial and convert it to integer
void setup() {
    Serial.begin(9600);
    Serial.println("Enter a number:");
}

void loop() {
    if (Serial.available()) {
        int num = Serial.parseInt(); // Read an integer
        Serial.print("Double of ");
        Serial.print(num);
        Serial.print(" is ");
        Serial.println(num * 2);
    }
}
