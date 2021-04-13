#include "pixels.h"
#include <Arduino.h>
#include <util/delay.h>

#define T1H 900 // Width of a 1 bit in ns
#define T1L 350 // Width of a 1 bit in ns

#define T0H 350 // Width of a 0 bit in ns
#define T0L 900 // Width of a 0 bit in ns

#define NS_PER_SEC (1000000000L)
#define CYCLES_PER_SEC (F_CPU)
#define NS_PER_CYCLE (NS_PER_SEC / CYCLES_PER_SEC)
#define NS_TO_CYCLES(n) ((n) / NS_PER_CYCLE)

#define showWord_its() this->setWordColor(141, 3)
#define showWord_about(offset) this->setWordColor(135, 5)
#define showWord_twenty() this->setWordColor(120, 6)
#define showWord_ten() this->setWordColor(127, 3)
#define showWord_five() this->setWordColor(116, 4)
#define showWord_quarter() this->setWordColor(108, 7)
#define showWord_minutes() this->setWordColor(96, 7)
#define showWord_half() this->setWordColor(103, 4)
#define showWord_to() this->setWordColor(94, 2)
#define showWord_past() this->setWordColor(90, 4)
#define showWord_oneh() this->setWordColor(72, 3)
#define showWord_twoh() this->setWordColor(75, 3)
#define showWord_threeh() this->setWordColor(78, 5)
#define showWord_fourh() this->setWordColor(68, 4)
#define showWord_fiveh() this->setWordColor(85, 4)
#define showWord_sixh() this->setWordColor(65, 3)
#define showWord_sevenh() this->setWordColor(60, 5)
#define showWord_eighth() this->setWordColor(48, 5)
#define showWord_nineh() this->setWordColor(53, 4)
#define showWord_tenh() this->setWordColor(57, 3)
#define showWord_elevenh() this->setWordColor(42, 6)
#define showWord_twelveh() this->setWordColor(36, 6)
#define showWord_oclock() this->setWordColor(24, 6)
#define showWord_time() this->setWordColor(31, 4)
#define showWord_for() this->setWordColor(21, 3)
#define showWord_a() this->setWordColor(19, 1)
#define showWord_coffee() this->setWordColor(12, 6)
#define showWord_tea() this->setWordColor(0, 3)
#define showWord_lunch() this->setWordColor(3, 5)
#define showWord_home() this->setWordColor(7, 4)
#define showWord_exclamation() this->setWordColor(11, 1)

void sendPixel(unsigned char r, unsigned char g, unsigned char b);

void Pixels::begin()
{
	pinMode(PIXELS_OUTPUT_PIN, OUTPUT);
};

void Pixels::clear()
{
	for (uint8_t i = 0; i < NUM_PIXELS; i++)
	{
		pixelmap[i] = 0;
	}
};

void Pixels::setPixelColor(uint8_t i, uint8_t colormap)
{
	pixelmap[i] = colormap;
};

void Pixels::setWordColor(uint8_t start_i, uint8_t len, uint8_t colormap)
{
	for (uint8_t i = 0; i < len; i++)
	{
		pixelmap[start_i + i] = colormap;
	}
}

void Pixels::show()
{
	cli();
	for (uint8_t i = 0; i < NUM_PIXELS; i++)
	{
		unsigned char value = pixelmap[i] << 3;
		sendPixel(value, value, value);
	}

	delay(5);
	sei();
};

void Pixels::setTime(uint8_t hour, uint8_t minute)
{
	showWord_its();

	if (minute % 5 != 0)
	{
		showWord_about(minute % 5);
	}

	uint8_t minute_selector = (minute / 5) % 12;
	switch (minute_selector)
	{
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

inline void sendBit(bool bitVal)
{
	if (bitVal)
	{
		asm volatile(
			"sbi %[port], %[bit] \n\t" // Set the output bit
			".rept %[onCycles] \n\t"   // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t"
			"cbi %[port], %[bit] \n\t" // Clear the output bit
			".rept %[offCycles] \n\t"  // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t" ::
				[port] "I"(_SFR_IO_ADDR(PORTB)),
			[bit] "I"(PB4),
			[onCycles] "I"(NS_TO_CYCLES(T1H) - 2),
			[offCycles] "I"(NS_TO_CYCLES(T1L) - 2));
	}
	else
	{
		asm volatile(
			"sbi %[port], %[bit] \n\t" // Set the output bit
			".rept %[onCycles] \n\t"   // Now timing actually matters. The 0-bit must be long enough to be detected but not too long or it will be a 1-bit
			"nop \n\t"				   // Execute NOPs to delay exactly the specified number of cycles
			".endr \n\t"
			"cbi %[port], %[bit] \n\t" // Clear the output bit
			".rept %[offCycles] \n\t"  // Execute NOPs to delay exactly the specified number of cycles
			"nop \n\t"
			".endr \n\t" ::
				[port] "I"(_SFR_IO_ADDR(PORTB)),
			[bit] "I"(PB4),
			[onCycles] "I"(NS_TO_CYCLES(T0H) - 2),
			[offCycles] "I"(NS_TO_CYCLES(T0L) - 2));
	}
}

inline void sendByte(unsigned char byte)
{
	for (unsigned char bit = 0; bit < 8; bit++)
	{
		// Neopixel wants bit in highest-to-lowest order
		sendBit(bitRead(byte, 7));
		// so send highest bit (bit #7 in an 8-bit byte since they start at 0)
		byte <<= 1; // and then shift left so bit 6 moves into 7, 5 moves into 6, etc
	}
}

inline void sendPixel(unsigned char r, unsigned char g, unsigned char b)
{
	sendByte(g); // Neopixel wants colors in green then red then blue order
	sendByte(r);
	sendByte(b);
}