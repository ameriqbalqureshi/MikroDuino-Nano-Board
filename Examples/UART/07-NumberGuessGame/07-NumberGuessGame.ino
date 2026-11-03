// Number Guessing Game
int targetNumber;  // The number to guess
bool gameActive = false; // Track game state

void setup() {
    Serial.begin(9600);  // Initialize Serial Communication
    Serial.println("Welcome to the Number Guessing Game!");
    Serial.println("Type 'start' to begin.");
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readString();  // Read user input
        input.trim();  // Remove any newline characters

        if (input == "start") {
            startGame();
        } 
        else if (gameActive) {
            int guess = input.toInt();  // Convert input to integer
            
            if (guess >= 1 && guess <= 100) {
                checkGuess(guess);
            } else {
                Serial.println("Invalid input! Enter a number between 1 and 100.");
            }
        } 
        else {
            Serial.println("Type 'start' to begin a new game.");
        }
    }
}

// Function to start a new game
void startGame() {
    targetNumber = random(1, 101);  // Pick a random number between 1 and 100
    gameActive = true;
    Serial.println("Game started! Guess a number between 1 and 100.");
}

// Function to check the user's guess
void checkGuess(int guess) {
    if (guess > targetNumber) {
        Serial.println("Too High! Try again.");
    } 
    else if (guess < targetNumber) {
        Serial.println("Too Low! Try again.");
    } 
    else {
        Serial.println("🎉 Congratulations! You guessed the correct number! 🎉");
        Serial.println("Type 'start' to play again.");
        gameActive = false;  // End the game
    }
}
