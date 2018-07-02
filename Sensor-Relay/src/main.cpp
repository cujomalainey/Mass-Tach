#include <Arduino.h>
#include "ant-controller.h"

void setup() {
    ant_init();
}

void loop() {
    ant_tick();
}


