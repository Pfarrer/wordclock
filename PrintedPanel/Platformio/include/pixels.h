#ifndef PIXELS_H
#define PIXELS_H

#define PIXELS_OUTPUT_PIN PB4
#define NUM_PIXELS 144
#define COLOR_DEFAULT 0b00000011

#include <stdint.h>
#include <stdlib.h>

class Pixels {
private:
    uint8_t *pixelmap;

public:
    Pixels() {
        pixelmap = (uint8_t*) malloc(NUM_PIXELS);
    };
    void begin();
    void clear();
    void setPixelColor(uint8_t, uint8_t);
    void setWordColor(uint8_t, uint8_t, uint8_t colormap=COLOR_DEFAULT);
    void setTime(uint8_t, uint8_t);
    void show();
};

#endif
