#include <Wire.h>
#include "DS3231.h"
#include <avr/sleep.h>
#include <avr/power.h>

#define RTC_INTERRUPT_PIN 2

RTClib RTC;
DS3231 Clock{};

void rtcInterrupt(void)
{
  /* This will bring us back from sleep. */
  
  /* We detach the interrupt to stop it from 
   * continuously firing while the interrupt pin
   * is low.
   */
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
  //sleep_disable();
}


void setup () {
  Serial.begin(57600);
  
  Wire.begin();
  Clock.setA1Time(2, 2, 27, 30 , 0x0, true, false, false);
  Clock.turnOnAlarm(1);
  
  pinMode(RTC_INTERRUPT_PIN, INPUT_PULLUP);
  Serial.println("Init complete");
}

void loop () {
  DateTime now = RTC.now();
  
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
  Serial.print(" C");
  
  Serial.println();

  enterSleep();
}
