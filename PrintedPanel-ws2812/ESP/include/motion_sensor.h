#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

#include <Arduino.h>

#define MOTION_SENSOR_PIN D2
#define MOTION_TIMEOUT_MILLIS 100

void motion_sensor_init();
void motion_sensor_loop();
bool motion_sensor_has_motion();

#endif