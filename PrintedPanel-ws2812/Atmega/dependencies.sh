#!/bin/sh

mkdir -p dependencies
cd dependencies

if [ ! -d "ArduinoCore-avr-1.8.2" ] 
then
    wget https://github.com/arduino/ArduinoCore-avr/archive/1.8.2.zip
    unzip 1.8.2.zip
    rm 1.8.2.zip
fi

if [ ! -d "DS3231-1.0.3" ] 
then
    wget https://github.com/NorthernWidget/DS3231/archive/v1.0.3.zip
    unzip v1.0.3.zip
    rm v1.0.3.zip
fi

if [ ! -d "light_ws2812-master" ] 
then
    wget https://github.com/cpldcpu/light_ws2812/archive/master.zip
    unzip master.zip
    rm master.zip
fi

if [ ! -d "avr-libc-2.0.0" ] 
then
    wget http://download.savannah.gnu.org/releases/avr-libc/avr-libc-2.0.0.tar.bz2
    tar xvf avr-libc-2.0.0.tar.bz2
    rm avr-libc-2.0.0.tar.bz2
fi
