#include "debug.h"
#include <Preferences.h>

Preferences pref;

void config_init() {
    DEBUG("Config: Init started");
    pref.begin("identity");
    DEBUG("Config: I am ", whoami());
    DEBUG("Config: Init completed");
}

uint8_t whoami() {
    return pref.getUChar("id");
}
