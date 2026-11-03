// Liquid Crystal Library Demonstration
#include <LiquidCrystal.h>

// Initialize the LCD with RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// Define a custom character (heart symbol)
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

void setup() {
  lcd.begin(16, 2);            // Set up the LCD's number of columns and rows
  lcd.createChar(0, heart);    // Create custom character at location 0
}

void loop() {
  demoPrint();
  demoCursor();
  demoBlink();
  demoScrollLeft();
  demoScrollRight();
  demoTextDirection();
  demoAutoscroll();
  demoDisplayToggle();
  demoCustomChar();
  demoFinish();
}

// Print "Hello, World!" and delay
void demoPrint() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(2000);
}

// Show and hide cursor
void demoCursor() {
  lcd.clear();
  lcd.print("Cursor Test");
  lcd.setCursor(13, 1);
  lcd.cursor();        // Show cursor
  delay(2000);
  lcd.noCursor();      // Hide cursor
}

// Show and stop blinking cursor
void demoBlink() {
  lcd.clear();
  lcd.print("Blink Cursor");
  lcd.setCursor(13, 0);
  lcd.blink();         // Enable blinking
  delay(2000);
  lcd.noBlink();       // Disable blinking
}

// Scroll text to the left
void demoScrollLeft() {
  lcd.clear();
  lcd.print("Scroll Left >>>");
  delay(1000);
  for (int i = 0; i < 5; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  }
}

// Scroll text to the right
void demoScrollRight() {
  lcd.clear();
  lcd.print("<<< Scroll Right");
  delay(1000);
  for (int i = 0; i < 5; i++) {
    lcd.scrollDisplayRight();
    delay(300);
  }
}

// Demonstrate changing text direction
void demoTextDirection() {
  lcd.clear();
  lcd.leftToRight();    // Default text direction
  lcd.setCursor(0, 0);
  lcd.print("LTR Text");
  delay(1000);

  lcd.rightToLeft();    // Reverse text direction
  lcd.setCursor(15, 1);
  lcd.print("RTL Text");
  delay(2000);

  lcd.leftToRight();    // Restore direction
}

// Demonstrate autoscroll effect
void demoAutoscroll() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.autoscroll();   // Enable autoscroll
  const char* word = "AutoScroll";
  for (int i = 0; word[i] != '\0'; i++) {
    lcd.print(word[i]);
    delay(300);
  }
  lcd.noAutoscroll(); // Disable autoscroll
  delay(1000);
}

// Turn display off and on again
void demoDisplayToggle() {
  lcd.clear();
  lcd.print("Display OFF");
  delay(1000);
  lcd.noDisplay();   // Turn off display
  delay(1500);
  lcd.display();     // Turn display back on
  delay(1000);
}

// Show custom character
void demoCustomChar() {
  lcd.clear();
  lcd.print("Custom Char: ");
  lcd.write(byte(0));  // Display the custom heart character
  delay(3000);
}

// End of demo message
void demoFinish() {
  lcd.clear();
  lcd.print("Demo Over!");
  delay(2000);
}
