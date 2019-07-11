#ifndef DEFINE_h
#define DEFINE_h

/**********
 * Contains system/build independent configuration details
 *********/

// Time Defines
#define MILLIS_TO_SECONDS 1000
#define SECONDS_TO_MINUTES 60

// ANT Defines
#define ANT_NUM_CHANNELS 15

// ANT+ Defines
#define CADENCE_SENSOR_DEVICE_TYPE 122
#define CADENCE_SENSOR_TRANSMISSION_PERIOD 8102
#define SPEED_SENSOR_DEVICE_TYPE   123
#define SPEED_SENSOR_TRANSMISSION_PERIOD 8118

// Display Defines
#define DISPLAY_ADDR 0x70

#define DISPLAY_ERROR_BLINK_RATE 2

// #define SERIAL_DEBUG_SEPARATOR ": "

// MQTT Defines
#define URI_MAX_LEN 32
#define NANOPB_MESSAGE_BUFFER_SIZE 256

// Macros
#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))

#endif // DEFINE_h
