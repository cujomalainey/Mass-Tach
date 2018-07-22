#include <Arduino.h>
#include "ant-controller.h"
#include "display-controller.h"
#include "mqtt-controller.h"
#include "config.h"
#include <SerialDebug.h>
#include <Preferences.h>

#if defined(ESP32)
HardwareSerial Serial1(2);
#endif

void setup() {
    SERIAL_DEBUG_SETUP(SERIAL_DEBUG_BAUD);
    display_init();
    ant_init();
    mqtt_init();
}

void loop() {
    ant_tick();
    mqtt_tick();
    display_tick();
}


