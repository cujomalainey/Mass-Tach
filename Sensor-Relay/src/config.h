#ifndef CONFIG_h
#define CONFIG_h

#include <Arduino.h>

/*
 * Pin and Harware Defines
 */
#define ANT_RESET_PIN 33
#define ANT_SLEEP_PIN 27
#define ANT_SUSPEND_PIN 4
#define ANT_BR1_PIN 32
#define ANT_BR2_PIN 21
#define ANT_BR3_PIN 14

#define VBAT_PIN A13

#define DEBUG_SERIAL Serial
#define ANT_SERIAL   Serial1

#define SERIAL_DEBUG_BAUD 115200

/*
 * System Config
 */

#define SERIAL_DEBUG true

uint8_t whoami(void);

#endif // CONFIG_h
