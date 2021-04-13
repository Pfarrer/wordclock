#include "motion_sensor.h"

unsigned long last_motion_millis;

void motion_sensor_init()
{
  pinMode(MOTION_SENSOR_PIN, INPUT);
  last_motion_millis = millis();
}

void motion_sensor_loop()
{
  int has_motion = digitalRead(MOTION_SENSOR_PIN);
  if (has_motion)
  {
    Serial.println("Seeing motion");
    last_motion_millis = millis();
  } else {
    Serial.println("No motion here");
  }
}

bool motion_sensor_has_motion()
{
  Serial.printf("Has motion: %i\n", millis() - last_motion_millis < MOTION_TIMEOUT_MILLIS);
  return millis() - last_motion_millis < MOTION_TIMEOUT_MILLIS;
}