#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "define.h"
#include "config.h"
#include "SerialDebug.h"
#include "display-controller.h"

Adafruit_AlphaNum4 display = Adafruit_AlphaNum4();

static const char* display_strings[] = {
    "ANT ",
    "BOOT",
    "CONF",
    "DIAG",
    "ME!!",
    "MQTT",
    "USB ",
    "WIFI",
};

void display_message(enum display_msgs idx) {
    if (idx == DISPLAY_NONE) {
        display.clear();
        display.writeDisplay();
        return;
    }

    display.writeDigitAscii(0, *display_strings[idx]);
    display.writeDigitAscii(1, *(display_strings[idx]+1));
    display.writeDigitAscii(2, *(display_strings[idx]+2));
    display.writeDigitAscii(3, *(display_strings[idx]+3));
    display.writeDisplay();
}

void display_error(enum display_msgs idx) {
    display.blinkRate(DISPLAY_ERROR_BLINK_RATE);
    display_message(idx);
}

void display_init() {
    DEBUG("Display: Init Started");
    display.begin(DISPLAY_ADDR);
    display.clear();
    display_message(DISPLAY_BOOT);
    DEBUG("Display: Init Completed");
}

void display_tick() {
}
