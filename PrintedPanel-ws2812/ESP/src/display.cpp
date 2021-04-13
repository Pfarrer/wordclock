#include "display.h"

void set_n_pixels(Adafruit_NeoPixel* pixels, uint8_t start, uint8_t n, uint32_t color) {
	for (uint8_t i = 0; i < n; i++) {
        pixels->setPixelColor(start + i, color);
    }
}

void set_word_its(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 141, 3, color); }
void set_word_about(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 135, 5, color); }
void set_word_twenty(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 120, 6, color); }
void set_word_ten(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 127, 3, color); }
void set_word_five(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 116, 4, color); }
void set_word_quarter(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 108, 7, color); }
void set_word_minutes(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 96, 7, color); }
void set_word_half(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 103, 4, color); }
void set_word_to(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 94, 2, color); }
void set_word_past(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 90, 4, color); }
void set_word_oneh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 72, 3, color); }
void set_word_twoh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 75, 3, color); }
void set_word_threeh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 78, 5, color); }
void set_word_fourh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 68, 4, color); }
void set_word_fiveh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 85, 4, color); }
void set_word_sixh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 65, 3, color); }
void set_word_sevenh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 60, 5, color); }
void set_word_eighth(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 48, 5, color); }
void set_word_nineh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 53, 4, color); }
void set_word_tenh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 57, 3, color); }
void set_word_elevenh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 42, 6, color); }
void set_word_twelveh(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 36, 6, color); }
void set_word_oclock(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 24, 6, color); }
void set_word_time(Adafruit_NeoPixel* pixels, uint32_t color) { set_n_pixels(pixels, 31, 4, color); }

void set_words(Adafruit_NeoPixel* pixels, uint8_t hour, uint8_t minute, uint32_t color) {
	set_word_its(pixels, color);

	if (minute % 5 != 0)
	{
		set_word_about(pixels, color);
	}

	uint8_t minute_selector = (minute / 5) % 12;
	switch (minute_selector)
	{
	case 0:
		set_word_oclock(pixels, color);
		break;
	case 1:
		set_word_five(pixels, color);
		set_word_minutes(pixels, color);
		set_word_past(pixels, color);
		break;
	case 2:
		set_word_ten(pixels, color);
		set_word_minutes(pixels, color);
		set_word_past(pixels, color);
		break;
	case 3:
		set_word_quarter(pixels, color);
		set_word_past(pixels, color);
		break;
	case 4:
		set_word_twenty(pixels, color);
		set_word_minutes(pixels, color);
		set_word_past(pixels, color);
		break;
	case 5:
		set_word_twenty(pixels, color);
		set_word_five(pixels, color);
		set_word_minutes(pixels, color);
		set_word_past(pixels, color);
		break;
	case 6:
		set_word_half(pixels, color);
		set_word_past(pixels, color);
		break;
	case 7:
		set_word_twenty(pixels, color);
		set_word_five(pixels, color);
		set_word_minutes(pixels, color);
		set_word_to(pixels, color);
		break;
	case 8:
		set_word_twenty(pixels, color);
		set_word_minutes(pixels, color);
		set_word_to(pixels, color);
		break;
	case 9:
		set_word_quarter(pixels, color);
		set_word_to(pixels, color);
		break;
	case 10:
		set_word_ten(pixels, color);
		set_word_minutes(pixels, color);
		set_word_to(pixels, color);
		break;
	case 11:
		set_word_five(pixels, color);
		set_word_minutes(pixels, color);
		set_word_to(pixels, color);
		break;
	}

	if (minute_selector > 6)
	{
		// show hour + 1
		hour = (hour + 1) % 12;
	}
	else
	{
		hour = hour % 12;
	}

	switch (hour)
	{
	case 0:
		set_word_twelveh(pixels, color);
		break;
	case 1:
		set_word_oneh(pixels, color);
		break;
	case 2:
		set_word_twoh(pixels, color);
		break;
	case 3:
		set_word_threeh(pixels, color);
		break;
	case 4:
		set_word_fourh(pixels, color);
		break;
	case 5:
		set_word_fiveh(pixels, color);
		break;
	case 6:
		set_word_sixh(pixels, color);
		break;
	case 7:
		set_word_sevenh(pixels, color);
		break;
	case 8:
		set_word_eighth(pixels, color);
		break;
	case 9:
		set_word_nineh(pixels, color);
		break;
	case 10:
		set_word_tenh(pixels, color);
		break;
	case 11:
		set_word_elevenh(pixels, color);
		break;
	}
}

void display_time(Adafruit_NeoPixel* pixels, struct tm* timeinfo, bool has_motion) {
  pixels->clear();

  uint32_t color;
  if (has_motion) {
    color = pixels->Color(20, 20, 20);
  } else {
    color = pixels->Color(1, 1, 1);
  }
  
  set_words(pixels, timeinfo->tm_hour, timeinfo->tm_min, color);
  
  pixels->show();
}

void display_greeting(Adafruit_NeoPixel* pixels) {
  pixels->clear();

  uint32_t color = pixels->Color(5, 30, 120);
  set_word_time(pixels, color);

  pixels->show();
}
