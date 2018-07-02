#ifndef DEFINES_h
#define DEFINES_h

#include <Arduino.h>
#include "constants.h"

extern HardwareSerial Serial1;

/*
 * Pin and Harware Defines
 */
// TODO update for feather
#define ANT_RESET_PIN -1
#define ANT_SLEEP_PIN -1
#define ANT_SUSPEND_PIN -1
#define ANT_BR1_PIN -1
#define ANT_BR2_PIN -1
#define ANT_BR3_PIN -1

#define DEBUG_SERIAL Serial
#define ANT_SERIAL   Serial1

/*
 * System Config
 */

#define USB_DEBUG_ENABLED 1
#define USB_DEBUG_LEVEL USB_DEBUG_LEVEL_WARNING

#endif // DEFINES_h
