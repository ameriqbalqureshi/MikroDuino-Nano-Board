// DS1307 RTC test program
#include <Wire.h>      // Include the Wire library for I2C communication
#include <RTClib.h>    // Include the RTClib library for RTC functions

RTC_DS1307 rtc;        // Create an RTC object

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
  if (!rtc.begin()) {  // Initialize the RTC
    Serial.println("Couldn't find RTC");
    while (1);         // Stop the program if RTC is not found
  }

  if (!rtc.isrunning()) { // Check if the RTC is running
    Serial.println("RTC is NOT running!");
    //Uncomment the next line to set the RTC to the time when the sketch is compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();  // Read current time and date from RTC

  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second());
  Serial.println();

  delay(1000);  // Wait for 1 second before updating the time again
}
