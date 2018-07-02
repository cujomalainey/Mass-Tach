#include <Arduino.h>
#include "ant-controller.h"

#if defined(ESP32)
HardwareSerial Serial1(2);
#endif

void setup() {
    ant_init();
}

void loop() {
    ant_tick();
}


