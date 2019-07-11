// This example uses an Adafruit Huzzah ESP8266
// to connect to shiftr.io.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Joël Gähwiler
// https://github.com/256dpi/arduino-mqtt

#include <WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <MQTT.h>
#include <Battery.h>
#include "mqtt-controller.h"
#include "display-controller.h"
#include "debug.h"
#include "secret.h"

WiFiClient net;
MQTTClient client;
Battery battery(3000, 4200, A13);

unsigned long lastMillis = 0;
char publishUri[URI_MAX_LEN];
uint8_t nanoPbBuffer[NANOPB_MESSAGE_BUFFER_SIZE];

void connect() {
  DEBUG("MQTT: Init Started");
  display_message(DISPLAY_WIFI);
  DEBUG("MQTT: checking WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  DEBUG("MQTT: WiFi connected");
  display_message(DISPLAY_MQTT);

  DEBUG("MQTT: connecting...");
  while (!client.connect("arduino", "try", "try")) {
    delay(1000);
  }
  DEBUG("MQTT: connected to MQTT server");

  DEBUG("BATTERY: Setting Up...");
  battery.begin(3300, 2.0, &sigmoidal);
  // TODO something to identify we booted
  client.publish("/hello", "");
}

void messageReceived(String &topic, String &payload) {
  DEBUG("incoming: " + topic + " - " + payload);
}

void mqtt_init() {
  WiFi.begin(WIFI_SSID, WIFI_PSK);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin(MQTT_HOST, net);
  client.onMessage(messageReceived);

  connect();
}

void mqtt_tick() {
  // TODO handle delay
  if (!client.loop()) {
    // TODO handle errors
  }
  delay(10);  // <- fixes some issues with WiFi stability

  if (!client.connected()) {
    connect();
  }

  // publish a message roughly every second.
  if (millis() - lastMillis > 1000) {
    lastMillis = millis();
    client.publish("/hello", "world");
  }
}
