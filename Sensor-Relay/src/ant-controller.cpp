/*************************************************************
*
*         ANT Radio Controller Source file
*
*************************************************************/
#include <Arduino.h>
#include <ANT.h>
#include "define.h"
#include "config.h"
#include "ant-controller.h"
#include "secret.h"
#include "display-controller.h"
#include <SerialDebug.h>

/*
 * ANT+ Defines
 */
#define ANT_PLUS_FREQUENCY         57

#define ANT_PLUS_NETWORK_ID        0
#define ANT_PLUS_DEFAULT_TRANSMISSION_TYPE 0

#define DATAPAGE_SENSOR_COUNTS_ID  0
#define PAIRING_BIT_MASK 0x80

const static uint8_t ANT_PLUS_NETWORK_KEY[] = ANT_PLUS_NETWORK_KEY_SECRET;

static AntWithCallbacks ant = AntWithCallbacks();
static uint8_t num_active_channels = 0;
static uint32_t next_data_transmit = 0;

typedef struct {
    uint8_t device_type;
    uint16_t channel_period;
} ant_sensor_config_type;

typedef struct {
    bool active;
    uint16_t last_count;
    uint16_t current_count;
} ant_channel_status_type;

// Indices match ant_device_type
const static ant_sensor_config_type ant_channel_config[] = {
    {CADENCE_SENSOR_DEVICE_TYPE, CADENCE_SENSOR_TRANSMISSION_PERIOD}, // BIKE_CADENCE
    {SPEED_SENSOR_DEVICE_TYPE, SPEED_SENSOR_TRANSMISSION_PERIOD}, // BIKE_SPEED
};

static ant_channel_status_type ant_channel_status[ANT_NUM_CHANNELS];

static void ant_handle_message();
static void ant_setup_channel(uint8_t channel, uint32_t serial_number, ant_device_type device_type);
static void ant_check_messages();
static void ant_service_data();
static void ant_parse_broadcast_data(uint8_t channel_id, uint8_t* data);
static void ant_parse_channel_event(uint8_t channel_id, uint8_t code);
static void ant_open_channel(uint8_t channel);

void ant_init()
{
    DEBUG("ANT: Init Started");
    display_message(DISPLAY_ANT);
    pinMode(ANT_RESET_PIN, OUTPUT);
    pinMode(ANT_BR1_PIN, OUTPUT);
    pinMode(ANT_BR2_PIN, OUTPUT);
    pinMode(ANT_BR3_PIN, OUTPUT);
    digitalWrite(ANT_RESET_PIN, HIGH);
    digitalWrite(ANT_BR1_PIN, HIGH);
    digitalWrite(ANT_BR2_PIN, LOW);
    digitalWrite(ANT_BR3_PIN, HIGH);

    // TODO update baud rate
    ANT_SERIAL.begin(9600);
    ant.setSerial(ANT_SERIAL);

    ant_reset();
    DEBUG("ANT: Init Complete");
}

void ant_reset()
{
    StartUpMessage sum;
    digitalWrite(ANT_RESET_PIN, LOW);
    digitalWrite(ANT_RESET_PIN, HIGH);
    if(ant.waitFor(sum, ANT_BOOT_TIMEOUT)) {
       display_error(DISPLAY_ANT);
       DEBUG("ERROR: Failed to reboot ANT radio");
       while(1){}
    }
    if(ant.waitFor(sum, ANT_BOOT_TIMEOUT)) {
       display_error(DISPLAY_ANT);
       DEBUG("ERROR: Failed to reboot ANT radio");
       while(1){}
    }
    memset(ant_channel_status, 0, sizeof(ant_channel_status));
}

void ant_tick()
{
    ant_check_messages();
    ant_service_data();
}

static void ant_check_messages()
{
    ant.readPacket();
    if (ant.getResponse().isAvailable())
    {
        ant_handle_message();
    }
    else if (ant.getResponse().isError()) {
    }
}

static void ant_service_data()
{
    if (millis() >= next_data_transmit && num_active_channels != 0)
    {
    }
}

static void ant_setup_channel(uint8_t channel, uint32_t serial_number, ant_device_type device_type)
{
    AssignChannel ac;
    ChannelId ci;
    ChannelPeriod cp;
    ChannelRfFrequency crf;

    ac = AssignChannel();
    ac.setChannel(channel);
    ac.setChannelType(CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE);
    ac.setChannelNetwork(ANT_PLUS_NETWORK_ID);
    ant.send(ac);
    ant_check_messages();

    ci = ChannelId();
    ci.setChannel(channel);
    ci.setDeviceNumber(serial_number & 0xFFFF);
    ci.setDeviceType(ant_channel_config[device_type].device_type);
    ci.setTransmissionType(ANT_PLUS_DEFAULT_TRANSMISSION_TYPE);
    ant.send(ci);
    ant_check_messages();

    cp = ChannelPeriod();
    cp.setChannel(channel);
    cp.setPeriod(ant_channel_config[device_type].channel_period);
    ant.send(cp);
    ant_check_messages();

    crf = ChannelRfFrequency();
    crf.setChannel(channel);
    crf.setRfFrequency(ANT_PLUS_FREQUENCY);
    ant.send(crf);
    ant_check_messages();

    ant_open_channel(channel);
}

static void ant_open_channel(uint8_t channel)
{
    OpenChannel oc;
    oc = OpenChannel();
    oc.setChannel(channel);
    ant.send(oc);
    ant_check_messages();
}

static void ant_handle_message()
{
    uint8_t msgId = ant.getResponse().getMsgId();
    switch (msgId)
    {
        case CHANNEL_EVENT:
        {
            ChannelEventResponse cer = ChannelEventResponse();
            ant.getResponse().getChannelEventResponseMsg(cer);
            ant_parse_channel_event(cer.getChannelNumber(), cer.getCode());
            break;
        }

        case START_UP_MESSAGE:
        {
            StartUpMessage sum = StartUpMessage();
            ant.getResponse().getStartUpMsg(sum);

            SetNetworkKey snk;
            snk = SetNetworkKey();
            snk.setNetwork(ANT_PLUS_NETWORK_ID);
            snk.setKey((uint8_t*)ANT_PLUS_NETWORK_KEY);
            ant.send(snk);
            break;
        }

        case BROADCAST_DATA:
        {
            BroadcastData bd = BroadcastData();
            ant.getResponse().getBroadcastDataMsg(bd);
            ant_parse_broadcast_data(bd.getChannelNumber(), bd.getData());
            break;
            }

        default:
            break;
    }
}

static void ant_parse_broadcast_data(uint8_t channel_id, uint8_t* data)
{
    if (((~PAIRING_BIT_MASK) & data[0]) == DATAPAGE_SENSOR_COUNTS_ID)
    {
        uint16_t count = (data[7] << BITS_IN_BYTE) + data[6];
        if (ant_channel_status[channel_id].active == true)
        {
            ant_channel_status[channel_id].current_count += (uint16_t)(count - ant_channel_status[channel_id].last_count);
        }
        else
        {
            ant_channel_status[channel_id].active = true;
        }
        ant_channel_status[channel_id].last_count = count;
    }
}

static void ant_parse_channel_event(uint8_t channel_id, uint8_t code)
{
    switch (code)
    {
        case STATUS_RESPONSE_NO_ERROR:
        case STATUS_EVENT_RX_FAIL:
            break;

        case STATUS_EVENT_RX_SEARCH_TIMEOUT:
            // send message back to server (once error reporting implemented) that sensor was lost and retry
            ant_open_channel(channel_id);
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            break;

        default:
            break;
    }
}
