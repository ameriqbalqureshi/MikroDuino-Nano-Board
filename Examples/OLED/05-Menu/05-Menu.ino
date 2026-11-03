//Making a Menu System using S3 and S4 Buttons
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define BUTTON_DOWN 3
#define BUTTON_SELECT 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* menuItems[] = { "Start", "Settings", "About", "Exit" };
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
int currentSelection = 0;

bool lastDownState = HIGH;
bool lastSelectState = HIGH;

void setup() {
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.clearDisplay();
  display.display();
  showMenu();
}

void loop() {
  bool downState = digitalRead(BUTTON_DOWN);
  bool selectState = digitalRead(BUTTON_SELECT);

  if (downState == LOW && lastDownState == HIGH) {
    currentSelection = (currentSelection + 1) % menuLength;
    showMenu();
    delay(200);  // debounce
  }

  if (selectState == LOW && lastSelectState == HIGH) {
    handleSelection(currentSelection);
    delay(300);  // debounce
  }

  lastDownState = downState;
  lastSelectState = selectState;
}

void showMenu() {
  display.clearDisplay();
  display.setTextSize(1);
   for (int i = 0; i < menuLength; i++) {
    if (i == currentSelection) {
      display.setCursor(0, i * 12);
      display.print("> ");
    } else {
      display.setCursor(0, i * 12);
      display.print("  ");
    }
    display.print(menuItems[i]);
  }
  display.display();
}

void handleSelection(int selection) {
  display.clearDisplay();
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("You selected:");
  display.setCursor(0, 35);
  display.setTextSize(2);
  display.print(menuItems[selection]);
  display.display();

  delay(1500);  // Show the selection before returning
  showMenu();   // Go back to menu
}
