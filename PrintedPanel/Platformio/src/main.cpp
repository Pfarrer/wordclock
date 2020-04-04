#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>
#include "pixels.h"
#include <Wire.h>
#include "DS3231.h"

#define RTC_INTERRUPT_PIN PB3

Pixels pixels;
RTClib RTC;
DS3231 Clock{};

void enterSleep();
void pixels_showTime(uint8_t hour, uint8_t minute);
int dst_offset(DateTime);

ISR (PCINT0_vect) {
  // do something interesting here
}

void setup() {
  pixels.begin();
  Wire.begin();

  Clock.turnOffAlarm(1);
  Clock.turnOffAlarm(2);
  
  Clock.setA1Time(0, 0, 0, 0, 0xff, false, false, false);
  Clock.setA2Time(0, 0, 0, 0xff, false, false, false);
  // Clock.turnOnAlarm(1); // every second
  Clock.turnOnAlarm(2); // every minute

  // Interrupt setup
  pinMode(RTC_INTERRUPT_PIN, INPUT);
  digitalWrite(RTC_INTERRUPT_PIN, HIGH);  // internal pull-up
  PCMSK |= bit (RTC_INTERRUPT_PIN);
  GIFR |= bit (PCIF);
  GIMSK |= bit (PCIE);
}

void loop() {
  pixels.clear();

  DateTime now = RTC.now();
  // pixels.setTime(now.minute()%24, now.second());
  int hour = (now.hour() + dst_offset(now)) % 12;
  pixels.setTime(hour, now.minute());
  pixels.show();

  // Clear alarm registers
  Clock.checkIfAlarm(1);
  Clock.checkIfAlarm(2);

  enterSleep();
  // delay(100);
}

void enterSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  ADCSRA = 0;
  power_all_disable();
  sleep_enable();
  sleep_cpu();

  sleep_disable();
  power_all_enable();
}

/**
 * Code copied from https://forum.arduino.cc/index.php?topic=427021.0
 */
int dst_offset(DateTime now) {
  int DST = 0;

  // ********************* Calculate offset for Sunday *********************
  int y = now.year() % 2000;      // two digit year (required here)
  int x = (y + y/4 + 2) % 7;      // remainder will identify which day of month
                                  // is Sunday by subtracting x from the one
                                  // or two week window.  First two weeks for March
                                  // and first week for November
  // *********** Test DST: BEGINS on 2nd Sunday of March @ 2:00 AM *********
  if (now.month() == 3 && now.day() == (14 - x) && now.hour() >= 2) {                                   
    DST = 1;
  }
  if ((now.month() == 3 && now.day() > (14 - x)) || now.month() > 3) {
    DST = 1;
  }
  // ************* Test DST: ENDS on 1st Sunday of Nov @ 2:00 AM ************       
  if(now.month() == 11 && now.day() == (7 - x) && now.hour() >= 2) {
    DST = 0;
  }
  if((now.month() == 11 && now.day() > (7 - x)) || now.month() > 11 || now.month() < 3) {
    DST = 0;
  }
  return DST;
}