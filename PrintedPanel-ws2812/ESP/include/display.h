#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define DISPLAY_OUTPUT_PIN D5
#define DISPLAY_NUM_PIXELS 144

void display_time(Adafruit_NeoPixel*, struct tm*, bool);
void display_greeting(Adafruit_NeoPixel*);

#endif