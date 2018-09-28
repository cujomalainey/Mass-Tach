#include "debug.h"
#include <Preferences.h>

#define MAX_STR_LEN 60
#define INVALID_DEVICE_ID -1
#define ANTPLUS_KEY_SIZE 16
#define MQTT_URL_MAX_SIZE MAX_STR_LEN
#define CONFIG_DATE_MAX_SIZE MAX_STR_LEN
#define WIFI_SSID_MAX_SIZE MAX_STR_LEN
#define WIFI_PSK_MAX_SIZE MAX_STR_LEN

Preferences pref;

void config_init() {
    char buf[MAX_STR_LEN];
    DEBUG("Config: Init started");
    pref.begin("identity", true);
    DEBUG("Config: I am ", whoami());
    get_antplus_key((uint8_t*)buf);
    DEBUG("Config: My ANT+ key is ", buf);
    get_mqtt_url(buf);
    DEBUG("Config: My MQTT URL is ", buf);
    get_wifi_ssid(buf);
    DEBUG("Config: My WIFI SSID is ", buf);
    get_last_config_date(buf);
    DEBUG("Config: My Config was last writen on: ", buf);
    DEBUG("Config: Init completed");
}

int whoami() {
    return pref.getInt("id", INVALID_DEVICE_ID);
}

size_t get_antplus_key(uint8_t* buf) {
    return pref.getBytes("ant+", buf, ANTPLUS_KEY_SIZE);
}

size_t get_mqtt_url(char* buf) {
    return pref.getString("mqtt_url", buf, MQTT_URL_MAX_SIZE);
}

size_t get_wifi_ssid(char* buf) {
    return pref.getString("wifi_ssid", buf, WIFI_SSID_MAX_SIZE);
}

size_t get_wifi_psk(char* buf) {
    return pref.getString("wifi_psk", buf, WIFI_PSK_MAX_SIZE);
}

size_t get_last_config_date(char* buf) {
    return pref.getString("config_date", buf, CONFIG_DATE_MAX_SIZE);
}
