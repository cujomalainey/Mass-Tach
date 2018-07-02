#ifndef DEFINES_h
#define DEFINES_h

#include <Arduino.h>

extern HardwareSerial Serial1;

/*
 * Pin and Harware Defines
 */
// TODO update for feather
#define ANT_RESET_PIN  11

#define DEBUG_SERIAL Serial
#define ANT_SERIAL   Serial1

/*
 * System Config
 */

#define USB_DEBUG_ENABLED 1
#define USB_DEBUG_LEVEL 1

#endif // DEFINES_h
