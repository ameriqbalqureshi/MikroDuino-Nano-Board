#include <IRremote.h>
IRrecv receiver(A0);
// IRsend send;
decode_results results;
void setup() {
  Serial.begin(9600);
  receiver.enableIRIn();
  Serial.println("IR Remote");
}

void loop() {
  if (receiver.decode(&results)) {
    Serial.println(results.value, HEX);
    receiver.resume();
  }
}
