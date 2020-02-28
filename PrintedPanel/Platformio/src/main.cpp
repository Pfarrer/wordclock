#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>
#include "pixels.h"
#include <Wire.h>
#include "DS3231.h"

#define RTC_INTERRUPT_PIN PB3
#define DEBUG_PIN PB5

Pixels pixels;
RTClib RTC;
DS3231 Clock{};

void enterSleep();
void pixels_showTime(uint8_t hour, uint8_t minute);

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
  //Clock.turnOnAlarm(1); // every second
  Clock.turnOnAlarm(2); // every minute

  pinMode(DEBUG_PIN, OUTPUT);
  digitalWrite(DEBUG_PIN, HIGH);
  delay(500);
  digitalWrite(DEBUG_PIN, LOW);
  delay(500);

  // Interrupt setup
  pinMode(RTC_INTERRUPT_PIN, INPUT);
  digitalWrite(RTC_INTERRUPT_PIN, HIGH);  // internal pull-up
  PCMSK  |= bit (RTC_INTERRUPT_PIN);
  GIFR   |= bit (PCIF);
  GIMSK  |= bit (PCIE);
 }

void loop() {
  pixels.clear();
  DateTime now = RTC.now();

  //pixels.setTime(now.minute()%24, now.second());
  pixels.setTime(now.hour(), now.minute());
  pixels.show();

  // Clear alarm registers
  Clock.checkIfAlarm(1);
  Clock.checkIfAlarm(2);

  enterSleep();
  // delay(100);
}

void rtcInterrupt() {
  sleep_disable();
  detachInterrupt(0);
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
