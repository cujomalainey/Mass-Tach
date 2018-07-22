#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include "define.h"
#include "config.h"
#include "SerialDebug.h"
#include "display-controller.h"

Adafruit_AlphaNum4 display = Adafruit_AlphaNum4();

void display_init() {
    DEBUG("Display: Init Started");
    display.begin(DISPLAY_ADDR);
    display.clear();
    display.writeDisplay();
    DEBUG("Display: Init Completed");
}

void display_tick() {
}
