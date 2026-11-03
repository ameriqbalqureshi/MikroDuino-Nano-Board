// Simple Calculator
void setup() {
    Serial.begin(9600); // Initialize Serial Communication
    Serial.println("Simple Calculator");
    Serial.println("Enter an expression (e.g., 5 + 3) and press Enter:");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readString(); // Read user input
        input.trim(); // Remove spaces and newlines
        
        int num1, num2;
        char operation;
        
        // Scan input for a number, an operator, and another number
        if (sscanf(input.c_str(), "%d %c %d", &num1, &operation, &num2) == 3) {
            float result;
            bool validOperation = true;

            // Perform the calculation
            switch (operation) {
                case '+': result = num1 + num2; break;
                case '-': result = num1 - num2; break;
                case '*': result = num1 * num2; break;
                case '/': 
                    if (num2 != 0) result = (float)num1 / num2; 
                    else {
                        Serial.println("Error: Division by zero!");
                        validOperation = false;
                    }
                    break;
                default:
                    Serial.println("Error: Invalid operator! Use +, -, *, /");
                    validOperation = false;
            }

            // Print the result
            if (validOperation) {
                Serial.print("Result: ");
                Serial.println(result);
            }
        } 
        else {
            Serial.println("Invalid input! Use format: number operator number (e.g., 5 + 3)");
        }
        
        Serial.println("Enter another expression:");
    }
}
