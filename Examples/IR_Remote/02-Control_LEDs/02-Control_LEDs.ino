#include <IRremote.h>

const int RECV_PIN = A0;

const int redLED = 6;
const int greenLED = 7;
const int blueLED = 8;

// Replace these with your remote's button codes (use Serial Monitor to find them)
#define RED_BUTTON   0xFF6897
#define GREEN_BUTTON 0xFF9867
#define BLUE_BUTTON  0xFFB04F

IRrecv irrecv(RECV_PIN);
decode_results results;

bool redState = false;
bool greenState = false;
bool blueState = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.print("Received: 0x");
    Serial.println(results.value, HEX);

    switch (results.value) {
      case RED_BUTTON:
        redState = !redState;
        digitalWrite(redLED, redState);
        break;
      case GREEN_BUTTON:
        greenState = !greenState;
        digitalWrite(greenLED, greenState);
        break;
      case BLUE_BUTTON:
        blueState = !blueState;
        digitalWrite(blueLED, blueState);
        break;
      case 0xFFFFFFFF: // Repeat code
        // Optionally ignore or repeat last command
        break;
    }

    irrecv.resume(); // Prepare to receive the next value
  }
}
