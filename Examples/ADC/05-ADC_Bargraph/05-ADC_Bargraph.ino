// LED Bar Graph display on reading potentiometer

#define POT_PIN A7  // Potentiometer connected to A7
#define NUM_LEDS 8  // Number of LEDs

// LED Pins from D6 to D13
int ledPins[NUM_LEDS] = {6, 7, 8, 9, 10, 11, 12, 13};

void setup() {
    for (int i = 0; i < NUM_LEDS; i++) {
        pinMode(ledPins[i], OUTPUT);  // Set LED pins as output
    }
}

void loop() {
    int potValue = analogRead(POT_PIN);  // Read potentiometer value (0-1023)
    int ledLevel = map(potValue, 0, 1023, 0, NUM_LEDS); // Map to LED range (0-8)

    // Turn ON LEDs up to ledLevel
    for (int i = 0; i < NUM_LEDS; i++) {
        if (i < ledLevel) {
            digitalWrite(ledPins[i], HIGH);
        } else {
            digitalWrite(ledPins[i], LOW);
        }
    }
    
    delay(100); // Small delay for smooth updating
}
