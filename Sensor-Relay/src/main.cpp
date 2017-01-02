#include <Arduino.h>
#include "debug.h"
#include "ant-controller.h"
#include "xbee-controller.h"

void setup() {
    debug_init();
    ant_init();
    xbee_init();
}

void loop() {
    ant_tick();
    xbee_tick();
    debug_tick();
}


