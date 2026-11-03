// Number Guessing Game 2
int low = 1, high = 100, guess;
bool gameActive = false;

void setup() {
    Serial.begin(9600);  // Initialize Serial Communication
    Serial.println("Think of a number between 1 and 100.");
    Serial.println("Type 'start' when you're ready.");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readString();  // Read user input
        input.trim();  // Remove extra spaces and newline characters

        if (input == "start") {
            startGame();
        } 
        else if (gameActive) {
            if (input == "H") {
                high = guess - 1;
                makeGuess();
            } 
            else if (input == "L") {
                low = guess + 1;
                makeGuess();
            } 
            else if (input == "C") {
                Serial.println("🎉 Yay! I guessed your number! 🎉");
                Serial.println("Type 'start' to play again.");
                gameActive = false;
            } 
            else {
                Serial.println("Invalid input! Reply with 'H' for too high, 'L' for too low, or 'C' for correct.");
            }
        } 
        else {
            Serial.println("Type 'start' to begin the game.");
        }
    }
}

// Start a new game
void startGame() {
    low = 1;
    high = 100;
    gameActive = true;
    makeGuess();
}

// Make a guess using binary search
void makeGuess() {
    if (low <= high) {
        guess = (low + high) / 2;
        Serial.print("Is your number ");
        Serial.print(guess);
        Serial.println("? (Reply with 'H' for too high, 'L' for too low, 'C' for correct)");
    } else {
        Serial.println("Something went wrong! Let's start over. Type 'start' to try again.");
        gameActive = false;
    }
}
