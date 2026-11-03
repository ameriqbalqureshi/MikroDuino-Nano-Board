//RTC with buttons to set time and date
#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define BTN_SELECT    2   // Button to move selection
#define BTN_INC       3   // Button to increment
#define BTN_DEC       4   // Button to decrement
#define BTN_SAVE      5   // Button to save/exit

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS1307 rtc;

bool settingMode = false;
uint8_t selectedField = 0; // 0: Hour, 1: Minute, 2: Day, 3: Month, 4: Year

int setHour, setMinute, setDay, setMonth, setYear;
bool showColon = true;

void setup() {
  Wire.begin();
  rtc.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(BTN_INC, INPUT_PULLUP);
  pinMode(BTN_DEC, INPUT_PULLUP);
  pinMode(BTN_SAVE, INPUT_PULLUP);

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(__DATE__, __TIME__)); // Auto set time if RTC stopped
  }
}

void loop() {
  if (digitalRead(BTN_SELECT) == LOW) {
    delay(200); // Debounce
    if (!settingMode) {
      DateTime now = rtc.now();
      setHour = now.hour();
      setMinute = now.minute();
      setDay = now.day();
      setMonth = now.month();
      setYear = now.year();
      settingMode = true;
      selectedField = 0;
    } else {
      selectedField = (selectedField + 1) % 5; // Move to next field
    }
  }

  if (settingMode) {
    adjustDateTime();
    showSetTimeScreen();
  } else {
    showNormalClock();
  }

  if (settingMode && digitalRead(BTN_SAVE) == LOW) {
    delay(200); // Debounce
    rtc.adjust(DateTime(setYear, setMonth, setDay, setHour, setMinute, 0));
    settingMode = false;
  }
}

void adjustDateTime() {
  if (digitalRead(BTN_INC) == LOW) {
    delay(200);
    switch (selectedField) {
      case 0: setHour = (setHour + 1) % 24; break;
      case 1: setMinute = (setMinute + 1) % 60; break;
      case 2: setDay = (setDay % 31) + 1; break;
      case 3: setMonth = (setMonth % 12) + 1; break;
      case 4: setYear++; break;
    }
  }

  if (digitalRead(BTN_DEC) == LOW) {
    delay(200);
    switch (selectedField) {
      case 0: setHour = (setHour + 23) % 24; break;
      case 1: setMinute = (setMinute + 59) % 60; break;
      case 2: setDay = (setDay == 1) ? 31 : (setDay - 1); break;
      case 3: setMonth = (setMonth == 1) ? 12 : (setMonth - 1); break;
      case 4: setYear--; break;
    }
  }
}

void showNormalClock() {
  DateTime now = rtc.now();
  
  display.clearDisplay();
  
  display.setTextSize(3);
  display.setCursor(10, 10);
  
  if (now.hour() < 10) display.print('0');
  display.print(now.hour());
  
  if (showColon) display.print(':');
  else display.print(' ');
  
  if (now.minute() < 10) display.print('0');
  display.print(now.minute());

  display.setTextSize(1);
  display.setCursor(20, 50);
  if (now.day() < 10) display.print('0');
  display.print(now.day());
  display.print('/');
  if (now.month() < 10) display.print('0');
  display.print(now.month());
  display.print('/');
  display.print(now.year());

  display.display();

  showColon = !showColon;
  delay(1000);
}

void showSetTimeScreen() {
  display.clearDisplay();
  
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print((selectedField == 0) ? ">" : " ");
  if (setHour < 10) display.print('0');
  display.print(setHour);
  display.print(":");

  display.print((selectedField == 1) ? ">" : " ");
  if (setMinute < 10) display.print('0');
  display.print(setMinute);

  display.setTextSize(1);
  display.setCursor(0, 30);
  display.print((selectedField == 2) ? ">" : " ");
  if (setDay < 10) display.print('0');
  display.print(setDay);
  display.print("/");

  display.print((selectedField == 3) ? ">" : " ");
  if (setMonth < 10) display.print('0');
  display.print(setMonth);
  display.print("/");

  display.print((selectedField == 4) ? ">" : " ");
  display.print(setYear);

  display.setCursor(0, 55);
  display.setTextSize(1);
  display.println("Press Save to confirm");

  display.display();
}
