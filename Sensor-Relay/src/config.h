#ifndef CONFIG_h
#define CONFIG_h

#include <Arduino.h>

#define MAX_STR_LEN 60
#define INVALID_DEVICE_ID -1
#define ANTPLUS_KEY_SIZE 16
#define MQTT_URL_MAX_SIZE MAX_STR_LEN
#define CONFIG_DATE_MAX_SIZE MAX_STR_LEN
#define WIFI_SSID_MAX_SIZE MAX_STR_LEN
#define WIFI_PSK_MAX_SIZE MAX_STR_LEN

/**
 * Pin and Harware Defines
 */
#define ANT_RESET_PIN 33
#define ANT_SLEEP_PIN 27
#define ANT_SUSPEND_PIN 4
#define ANT_BR1_PIN 32
#define ANT_BR2_PIN 21
#define ANT_BR3_PIN 14

#define VBAT_PIN A13

/**
 * Serial port defines
 */
#define DEBUG_SERIAL Serial
#define USB_SERIAL   Serial
#define ANT_SERIAL   Serial1

#define SERIAL_DEBUG_BAUD 115200

#define SERIAL_DEBUG true

/**
 * Diagnostic Config
 */

#define DIAGNOSTIC_BOOT_ATTEMPTS 3
#define DIAGNOSTIC_BOOT_TIME 1000

/*
 * System Config
 */

int whoami(void);
size_t get_antplus_key(uint8_t* buf);
size_t get_mqtt_url(char* buf);
size_t get_wifi_ssid(char* buf);
size_t get_wifi_psk(char* buf);
size_t get_last_config_date(char* buf);

#endif // CONFIG_h
