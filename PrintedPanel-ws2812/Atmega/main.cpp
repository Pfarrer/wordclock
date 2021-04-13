#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include <DS3231.h>

extern "C" {
#include "light_ws2812.h"
}

#define RTC_INTERRUPT_PIN 2
#define DEBUG_LED_PIN PB1
#define NUM_PIXELS 144

#define setWord_its() pixels_setWord(141, 3)
#define setWord_about() pixels_setWord(135, 5)
#define setWord_twenty() pixels_setWord(120, 6)
#define setWord_ten() pixels_setWord(127, 3)
#define setWord_five() pixels_setWord(116, 4)
#define setWord_quarter() pixels_setWord(108, 7)
#define setWord_minutes() pixels_setWord(96, 7)
#define setWord_half() pixels_setWord(103, 4)
#define setWord_to() pixels_setWord(94, 2)
#define setWord_past() pixels_setWord(90, 4)
#define setWord_oneh() pixels_setWord(72, 3)
#define setWord_twoh() pixels_setWord(75, 3)
#define setWord_threeh() pixels_setWord(78, 5)
#define setWord_fourh() pixels_setWord(68, 4)
#define setWord_fiveh() pixels_setWord(85, 4)
#define setWord_sixh() pixels_setWord(65, 3)
#define setWord_sevenh() pixels_setWord(60, 5)
#define setWord_eighth() pixels_setWord(48, 5)
#define setWord_nineh() pixels_setWord(53, 4)
#define setWord_tenh() pixels_setWord(57, 3)
#define setWord_elevenh() pixels_setWord(42, 6)
#define setWord_twelveh() pixels_setWord(36, 6)
#define setWord_oclock() pixels_setWord(24, 6)
#define setWord_time() pixels_setWord(31, 4)
#define setWord_for() pixels_setWord(21, 3)
#define setWord_a() pixels_setWord(19, 1)
#define setWord_coffee() pixels_setWord(12, 6)
#define setWord_tea() pixels_setWord(0, 3)
#define setWord_lunch() pixels_setWord(3, 5)
#define setWord_home() pixels_setWord(7, 4)
#define setWord_exclamation() pixels_setWord(11, 1)

RTClib RTC;
DS3231 Clock{};
struct cRGB pixels[NUM_PIXELS];

void rtcInterrupt(void)
{
  sleep_disable();
  detachInterrupt(0);
}

void enterSleep(void)
{
  sleep_enable();
  
  attachInterrupt(0, rtcInterrupt, FALLING);
  delay(100);
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  sleep_cpu();
  
  /* The program will continue from here. */
  
  /* First thing to do is disable sleep. */
  sleep_disable();
}

void pixels_clear()
{
  for (uint8_t i=0; i<NUM_PIXELS; i++) {
    pixels[i].r = 0;
    pixels[i].g = 0;
    pixels[i].b = 0;
  }
}

void pixels_setWord(uint8_t start_idx, uint8_t len)
{
  for (uint8_t i=0; i<len; i++) {
    pixels[start_idx+i].r = 10;
    pixels[start_idx+i].g = 10;
    pixels[start_idx+i].b = 10;
  }
}

void pixels_setTime(uint8_t hour, uint8_t minute)
{
  setWord_its();
  
  if (minute % 5 != 0) {
    setWord_about();
  }

  uint8_t minute_selector = (minute / 5) % 12;
  switch (minute_selector) {
    case 0:
      setWord_oclock();
      break;
    case 1:
      setWord_five();
      setWord_minutes();
      setWord_past();
      break;
    case 2:
      setWord_ten();
      setWord_minutes();
      setWord_past();
      break;
    case 3:
      setWord_quarter();
      setWord_past();
      break;
    case 4:
      setWord_twenty();
      setWord_minutes();
      setWord_past();
      break;
    case 5:
      setWord_twenty();
      setWord_five();
      setWord_minutes();
      setWord_past();
      break;
    case 6:
      setWord_half();
      setWord_past();
      break;
    case 7:
      setWord_twenty();
      setWord_five();
      setWord_minutes();
      setWord_to();
      break;
    case 8:
      setWord_twenty();
      setWord_minutes();
      setWord_to();
      break;
    case 9:
      setWord_quarter();
      setWord_to();
      break;
    case 10:
      setWord_ten();
      setWord_minutes();
      setWord_to();
      break;
    case 11:
      setWord_five();
      setWord_minutes();
      setWord_to();
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
      setWord_twelveh();
      break;
    case 1:
      setWord_oneh();
      break;
    case 2:
      setWord_twoh();
      break;
    case 3:
      setWord_threeh();
      break;
    case 4:
      setWord_fourh();
      break;
    case 5:
      setWord_fiveh();
      break;
    case 6:
      setWord_sixh();
      break;
    case 7:
      setWord_sevenh();
      break;
    case 8:
      setWord_eighth();
      break;
    case 9:
      setWord_nineh();
      break;
    case 10:
      setWord_tenh();
      break;
    case 11:
      setWord_elevenh();
      break;
  }
}

void setup()
{
  pixels_clear();
  ws2812_setleds(pixels, NUM_PIXELS);
  
  Wire.begin();

  Clock.turnOffAlarm(1);
  Clock.turnOffAlarm(2);
  
  Clock.setA1Time(0, 0, 0, 0, 0xff, false, false, false);
  Clock.setA2Time(0, 0, 0, 0xff, false, false, false);
//  Clock.turnOnAlarm(1);
  Clock.turnOnAlarm(2);
  
  pinMode(RTC_INTERRUPT_PIN, INPUT);

  DDRB |= (1 << PB1);
  PORTB ^= (1 << PB1);
  _delay_ms(500);
}

void loop()
{
  DateTime now = RTC.now();

  PORTB ^= (1 << PB1);
  
  pixels_clear();
  //pixels_setTime(now.hour(), now.minute());
  pixels_setTime(3, 37);
  ws2812_setleds(pixels, NUM_PIXELS);

//  enterSleep();
  delay(1000);
}

int main()
{
  setup();
  for (;;) {
    loop();
  }
  return 0; 
}