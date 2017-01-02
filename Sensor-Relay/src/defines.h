#include <Arduino.h>
/*
 * Pin and Harware Defines
 */
#define ANT_RESET_PIN  11
#define XBEE_RESET_PIN 12

#define DEBUG_SERIAL_PORT Serial
#define ANT_SERIAL_PORT   Serial1
#define XBEE_SERIAL_PORT  Serial2
#define ANT_SERIAL_PORT_CTS_PIN 20
#define XBEE_SERIAL_PORT_CTS_PIN "NOT DEFINED"

#define BAUD_RATE 9600

/*
 * System Config
 */

#define DEBUG_ENABLED 1