#include "debug.h"
#include <Preferences.h>

Preferences pref;

void config_init() {
    DEBUG("Config: Init started");
    pref.begin("identity", true);
    DEBUG("Config: I am ", whoami());
    DEBUG("Config: My ANT+ key is ", get_antplus_key());
    DEBUG("Config: My MQTT URL is ", get_mqtt_url());
    DEBUG("Config: My WIFI SSID is ", get_wifi_ssid());
    DEBUG("Config: My Config was last writen on: ", )
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

bool get_wifi_ssid(char* buf) {
    pref.getString("wifi_ssid", buf, WIFI_SSID_MAX_SIZE);
}

bool get_wifi_psk(char* buf) {
    pref.getString("wifi_psk", buf, WIFI_PSK_MAX_SIZE);
}

bool get
