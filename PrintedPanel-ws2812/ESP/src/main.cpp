#include <Arduino.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <TZ.h>
#include <Adafruit_NeoPixel.h>

extern "C" {
  #include "user_interface.h"
}

#include "secrets.h"
#include "display.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "This ain't a ESP8266 or ESP32, dumbo!"
#endif

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

Adafruit_NeoPixel pixels(DISPLAY_NUM_PIXELS, DISPLAY_OUTPUT_PIN, NEO_GRB + NEO_KHZ800);

void setup_wifi() {
  Serial.print("\n\nChecking WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("connected (");
  Serial.print(WiFi.localIP());
  Serial.println(")");

  wifi_set_sleep_type(LIGHT_SLEEP_T);
}

void setup_time() {
  configTime(TZ_Europe_Berlin, "de.pool.ntp.org");
  timeClient.begin();
  timeClient.setUpdateInterval(60 * 60 * 1000);
}

void setup() {
  Serial.begin(115200);

  pixels.begin();
  display_greeting(&pixels);

  setup_wifi();
  setup_time();

  Serial.println("Setup done...");
}

struct tm* local_time() {
  timeClient.update();

  time_t rawtime;
  time(&rawtime);

  return localtime(&rawtime);
}

void loop() {
  struct tm* timeinfo = local_time();
  Serial.print(asctime(timeinfo));

  display_time(&pixels, timeinfo, true);

  if (timeinfo->tm_year == 1970) {
    // No updated time yet -> delay only one second to display the correct
    // time as soon as possible
    delay(1000);
  } else {
    delay(10000);
  }
}
