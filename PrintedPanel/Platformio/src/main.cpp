#define F_CPU 8000000UL

#include <avr/sleep.h>
#include <avr/power.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "DS3231.h"

#define RTC_INTERRUPT_PIN PB3
#define PIXELS_OUTPUT_PIN PB4
#define NUM_PIXELS 10

#define COLOR_DEFAULT pixels.Color(10, 10, 10)

Adafruit_NeoPixel pixels(NUM_PIXELS, PIXELS_OUTPUT_PIN, NEO_GRB + NEO_KHZ800);
RTClib RTC;
DS3231 Clock{};

void rtcInterrupt();
void enterSleep();

void setup() {
  pixels.begin();
  Wire.begin();

  Clock.turnOffAlarm(1);
  Clock.turnOffAlarm(2);
  
  Clock.setA1Time(0, 0, 0, 0, 0xff, false, false, false);
  Clock.setA2Time(0, 0, 0, 0xff, false, false, false);
  Clock.turnOnAlarm(1); // every second
  Clock.turnOnAlarm(2); // every minute

  pinMode(RTC_INTERRUPT_PIN, INPUT);
}

void loop() {
  pixels.clear();
  DateTime now = RTC.now();

  pixels.setPixelColor(now.second()%NUM_PIXELS, COLOR_DEFAULT);
  pixels.show();
  
  enterSleep();
}


void rtcInterrupt() {
  sleep_disable();
  detachInterrupt(0);
}

void enterSleep() {
  sleep_enable();
  
  attachInterrupt(0, rtcInterrupt, FALLING);
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_IDLE);
  
  sleep_cpu();
  
  /* The program will continue from here. */
  
  /* First thing to do is disable sleep. */
  sleep_disable();
}