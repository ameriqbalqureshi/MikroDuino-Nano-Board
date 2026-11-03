// Mikroduino Nano Arduino Learning Platform
// LED Test program

void setup() {
  // put your setup code here, to run once:
for(int i=3;i<14;i++){
  pinMode(i, OUTPUT);
  digitalWrite(i, LOW);
}
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i=3;i<14;i++){
    digitalWrite(i, HIGH);
    delay(100);
}
delay(1000);
for(int i=3;i<14;i++){
    digitalWrite(i, LOW);
    delay(100);
}
delay(1000);
}
