/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 modified 7 Nov 2016
 by Arturo Guadalupi

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld

*/

#include <avr/sleep.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char prefixes[4][17] = {
  " Halb           ",
  " Viertel vor    ",
  " Genau          ",
  " Viertel nach   ",
};

char hours[12][17] = {
  " Eins           ",
  " Zwei           ",
  " Drei           ",
  " Vier           ",
  " Fuenf          ",
  " Sechs          ",
  " Sieben         ",
  " Acht           ",
  " Neun           ",
  " Zehn           ",
  " Elf            ",
  " Zwoelf         "
};

int buttonPin = 8;
int lastButtonState = LOW;

void setup() {
  pinMode(buttonPin, INPUT);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
//  lcd.print("hello, world!");
}

int offset_minutes = 0;//9 * 60;

String toPrefix(int minutes) {
  return prefixes[(minutes / 15) % 4];
}

String toHour(int minutes) {
  return hours[(minutes / 60) % 12];
}

void loop() {
  int tmp_state = digitalRead(buttonPin);
  if (lastButtonState == LOW && tmp_state == HIGH) {
    offset_minutes = (offset_minutes + 15) % (12 * 60);
    lastButtonState = HIGH;
  } else if (lastButtonState == HIGH && tmp_state == LOW) {
    lastButtonState = LOW;
  }
  
  unsigned int seconds = millis() / 1000; 
  int minutes = seconds / 60 + offset_minutes;

  lcd.setCursor(0, 0);
  lcd.print(toPrefix(minutes));
  lcd.setCursor(0, 1);
  lcd.print(toHour(minutes));

  delay(100);
}

