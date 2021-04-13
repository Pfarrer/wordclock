DEVICE           = atmega328p
CLOCK            = 8000000
PROGRAMMER       = usbasp
BAUD             = 115200
FILENAME         = main

ARDUINO_LIB      = ./dependencies/ArduinoCore-avr-1.8.2/cores/arduino
ARDUINO_VARIANTS = ./dependencies/ArduinoCore-avr-1.8.2/variants/mega
WIRE_LIB         = ./dependencies/ArduinoCore-avr-1.8.2/libraries/Wire/src
DS3231_LIB       = ./dependencies/DS3231-1.0.3
WS2812_LIB       = ./dependencies/light_ws2812-master/light_ws2812_AVR/Light_WS2812
WS2812_ARGS      = -Dws2812_port=0 -Dws2812_port=B -Dws2812_resettime=300 -DWS2812_CONFIG_H_
CINCLUDES        = -I$(ARDUINO_LIB) -I$(ARDUINO_VARIANTS) -I$(WIRE_LIB) -I$(DS3231_LIB) -I$(WS2812_LIB)
CC               = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

all: clean build

wire.o:
	$(CC) -c $(WIRE_LIB)/Wire.cpp -o wire.o $(CINCLUDES)

twi.o:
	$(CC) -c $(WIRE_LIB)/utility/twi.c -o twi.o $(CINCLUDES)

ds3231.o:
	$(CC) -c $(DS3231_LIB)/DS3231.cpp -o ds3231.o $(CINCLUDES)

light_ws2812.o:
	$(CC) -c $(WS2812_LIB)/light_ws2812.c -o light_ws2812.o $(CINCLUDES)

hooks.o:
	$(CC) -c $(ARDUINO_LIB)/hooks.c -o hooks.o $(CINCLUDES)

wiring.o:
	$(CC) -c $(ARDUINO_LIB)/wiring.c -o wiring.o $(CINCLUDES)

wiring_digital.o:
	cd $(ARDUINO_LIB) && $(CC) -c wiring_digital.c -o wiring_digital.o -I. -I../../variants/standard && cd - && mv $(ARDUINO_LIB)/wiring_digital.o .

winterrupts.o:
	$(CC) -c $(ARDUINO_LIB)/WInterrupts.c -o winterrupts.o $(CINCLUDES)

libcore.a: wire.o twi.o ds3231.o light_ws2812.o winterrupts.o hooks.o wiring.o wiring_digital.o
	avr-ar rcs libcore.a wire.o twi.o ds3231.o light_ws2812.o winterrupts.o hooks.o wiring.o wiring_digital.o

$(FILENAME).hex: libcore.a
	$(CC) -c $(FILENAME).cpp -o $(FILENAME).o $(CINCLUDES)
	$(CC) -o $(FILENAME).elf $(FILENAME).o -L. -lcore
	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex

build: $(FILENAME).hex
	avr-size --format=avr --mcu=$(DEVICE) $(FILENAME).elf

upload: | all
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -b $(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm -f *.o *.elf *.hex *.a
