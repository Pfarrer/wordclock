#include <Wire.h>
#include "DS3231.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include <Adafruit_NeoPixel.h>

#define RTC_INTERRUPT_PIN 2
#define LED_OUTPUT_PIN 8
#define NUM_PIXELS 144

#define COLOR_DEFAULT pixels.Color(50, 50, 50)

#define showWord_its() pixels_showWord(141, 3)
#define showWord_about() pixels_showWord(135, 5)
#define showWord_twenty() pixels_showWord(120, 6)
#define showWord_ten() pixels_showWord(127, 3)
#define showWord_five() pixels_showWord(116, 4)
#define showWord_quarter() pixels_showWord(108, 7)
#define showWord_minutes() pixels_showWord(96, 7)
#define showWord_half() pixels_showWord(103, 4)
#define showWord_to() pixels_showWord(94, 2)
#define showWord_past() pixels_showWord(90, 4)
#define showWord_oneh() pixels_showWord(72, 3)
#define showWord_twoh() pixels_showWord(75, 3)
#define showWord_threeh() pixels_showWord(78, 5)
#define showWord_fourh() pixels_showWord(68, 4)
#define showWord_fiveh() pixels_showWord(85, 4)
#define showWord_sixh() pixels_showWord(65, 3)
#define showWord_sevenh() pixels_showWord(60, 5)
#define showWord_eighth() pixels_showWord(48, 5)
#define showWord_nineh() pixels_showWord(53, 4)
#define showWord_tenh() pixels_showWord(57, 3)
#define showWord_elevenh() pixels_showWord(42, 6)
#define showWord_twelveh() pixels_showWord(36, 6)
#define showWord_oclock() pixels_showWord(24, 6)
#define showWord_time() pixels_showWord(31, 4)
#define showWord_for() pixels_showWord(21, 3)
#define showWord_a() pixels_showWord(19, 1)
#define showWord_coffee() pixels_showWord(12, 6)
#define showWord_tea() pixels_showWord(0, 3)
#define showWord_lunch() pixels_showWord(3, 5)
#define showWord_home() pixels_showWord(7, 4)
#define showWord_exclamation() pixels_showWord(11, 1)

RTClib RTC;
DS3231 Clock{};
Adafruit_NeoPixel pixels(NUM_PIXELS, LED_OUTPUT_PIN, NEO_GRB + NEO_KHZ800);

void rtcInterrupt(void)
{
  sleep_disable();
  detachInterrupt(0);
  Serial.println("Just woke up...");
}

void enterSleep(void)
{
  Serial.println("Going to sleep...");
  
  sleep_enable();
  
  attachInterrupt(0, rtcInterrupt, FALLING);
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sleep_cpu();
  
  /* The program will continue from here. */
  
  /* First thing to do is disable sleep. */
  sleep_disable();
}


void setup ()
{
  Serial.begin(57600);

  pixels.begin();
  pixels.clear();
  
  Wire.begin();

  Clock.turnOffAlarm(1);
  Clock.turnOffAlarm(2);
  
  Clock.setA1Time(0, 0, 0, 0, 0xff, false, false, false);
  Clock.setA2Time(0, 0, 0, 0xff, false, false, false);
//  Clock.turnOnAlarm(1);
  Clock.turnOnAlarm(2);
  
  pinMode(RTC_INTERRUPT_PIN, INPUT);
  
  Serial.println("Init complete");
}

void loop ()
{
  DateTime now = RTC.now();

  serial_printTime(now);

  pixels.clear();
  pixels_showTime(now.hour(), now.minute());
  pixels.show();

  enterSleep();
  
  //delay(100);
}

void serial_printTime(DateTime now) {
  Serial.print(now.year(), DEC);
  Serial.print('-');
  Serial.print(now.month(), DEC);
  Serial.print('-');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);

  float temp = Clock.getTemperature();
  Serial.print(" -- ");
  Serial.print(temp);
  Serial.print(" C -- Alarm: [ ");

  bool alarm1 = Clock.checkIfAlarm(1);
  if (alarm1) {
    Serial.print("1! ");
  }
  
  bool alarm2 = Clock.checkIfAlarm(2);
  if (alarm2) {
    Serial.print("2! ");
  }
  
  Serial.println(']');
}

void pixels_showTime(uint8_t hour, uint8_t minute)
{
  showWord_its();
  
  if (minute % 5 != 0) {
    showWord_about();
  }

  uint8_t minute_selector = (minute / 5) % 12;
  switch (minute_selector) {
    case 0:
      showWord_oclock();
      break;
    case 1:
      showWord_five();
      showWord_minutes();
      showWord_past();
      break;
    case 2:
      showWord_ten();
      showWord_minutes();
      showWord_past();
      break;
    case 3:
      showWord_quarter();
      showWord_past();
      break;
    case 4:
      showWord_twenty();
      showWord_minutes();
      showWord_past();
      break;
    case 5:
      showWord_twenty();
      showWord_five();
      showWord_minutes();
      showWord_past();
      break;
    case 6:
      showWord_half();
      showWord_past();
      break;
    case 7:
      showWord_twenty();
      showWord_five();
      showWord_minutes();
      showWord_to();
      break;
    case 8:
      showWord_twenty();
      showWord_minutes();
      showWord_to();
      break;
    case 9:
      showWord_quarter();
      showWord_to();
      break;
    case 10:
      showWord_ten();
      showWord_minutes();
      showWord_to();
      break;
    case 11:
      showWord_five();
      showWord_minutes();
      showWord_to();
      break;
  }

  if (minute_selector > 6) {
    // show hour + 1
    hour = (hour + 1) % 12;
  } else {
    hour = hour % 12;
  }

  switch (hour) {
    case 0:
      showWord_twelveh();
      break;
    case 1:
      showWord_oneh();
      break;
    case 2:
      showWord_twoh();
      break;
    case 3:
      showWord_threeh();
      break;
    case 4:
      showWord_fourh();
      break;
    case 5:
      showWord_fiveh();
      break;
    case 6:
      showWord_sixh();
      break;
    case 7:
      showWord_sevenh();
      break;
    case 8:
      showWord_eighth();
      break;
    case 9:
      showWord_nineh();
      break;
    case 10:
      showWord_tenh();
      break;
    case 11:
      showWord_elevenh();
      break;
  }
}

void pixels_showWord(uint8_t start_idx, uint8_t len)
{
  for (uint8_t i=0; i<len; i++) {
    pixels.setPixelColor(start_idx+i, COLOR_DEFAULT);
  }
}

