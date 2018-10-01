#include <Arduino.h>
#include "ant-controller.h"
#include "display-controller.h"
#include "mqtt-controller.h"
#include "config.h"
#include "diagnostic.h"
#include <SerialDebug.h>
#include <Preferences.h>

void setup() {
    SERIAL_DEBUG_SETUP(SERIAL_DEBUG_BAUD);
    display_init();
    diagnostic_init();
    ant_init();
    mqtt_init();
}

void loop() {
    ant_tick();
    mqtt_tick();
    display_tick();
}


