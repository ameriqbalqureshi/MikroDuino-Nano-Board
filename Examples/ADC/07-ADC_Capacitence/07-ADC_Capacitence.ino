// ADC Measuring capacitence of an unknown capacitor.

const int chargePin = 7;      // Output to charge the capacitor
const int analogPin = A0;     // Analog input to monitor voltage
const int threshold = 645;  // 63.2% of 1023 (5V) ≈ 3.15V
const float R = 10000.0;      // 10k ohms

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Discharge capacitor
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
  delay(100);

  // Prepare to measure
  pinMode(chargePin, INPUT);  // Hi-Z state
  delay(10);

  // Start charging
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, HIGH);

  unsigned long startTime = micros();

  while (analogRead(analogPin) < threshold);  // Wait until 63%

  unsigned long elapsedTime = micros() - startTime;

  float capacitance = (float)elapsedTime / R;  // C in microfarads (μF)

  Serial.print("Time (us): ");
  Serial.print(elapsedTime);
  Serial.print(" | Capacitance (uF): ");
  Serial.println(capacitance);

  delay(2000);
}
