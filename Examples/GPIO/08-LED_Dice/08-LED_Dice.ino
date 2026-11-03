// MikroDuino Nano LED Random
// Set LEDs from D6 to D13 on Random
// Simulation of Dice, A random number is generated, and dice rolled for 10 times
// final dice is displayed and buzzer played
#define BUZZER 17 // Buzzer pin A3
int led;
void setup() {
  pinMode(BUZZER, OUTPUT);
  for (int i = 6; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); // Set LED OFF
  }
}
// LED Random
void loop() {
  for (int i = 0; i < 10; i++) {
    led = random(6, 12);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
  }
  digitalWrite(led, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER,LOW);
  delay(5000);
  digitalWrite(led, LOW);
}
