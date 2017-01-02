/*************************************************************
*
*         ANT Radio Controller Source file
*
*************************************************************/
#include <Arduino.h>
#include <ANT.h>
#include "defines.h"
#include "debug.h"
#include "ant-controller.h"
#include "xbee-controller.h"
#include "SensorData.pb.h"
#include "secret.h"

/*
 * ANT+ Defines
 */
#define CADENCE_SENSOR_DEVICE_TYPE 122
#define SPEED_SENSOR_DEVICE_TYPE   123
#define ANT_PLUS_FREQUENCY         57

#define ANT_PLUS_NETWORK_ID        0
#define ANT_PLUS_DEFAULT_TRANSMISSION_TYPE 0

#define DATAPAGE_SENSOR_COUNTS_ID  0
#define PAIRING_BIT_MASK 0x80

#define ANT_POLLING_PERIOD 0.1 //minutes
#define MILLIS_TO_SECONDES 1000
#define SECONDS_TO_MINUTES 60
#define SAMPLE_DELAY_IN_MILLIS MILLIS_TO_SECONDES*SECONDS_TO_MINUTES*ANT_POLLING_PERIOD

const static uint8_t ANT_PLUS_NETWORK_KEY[] = ANT_PLUS_NETWORK_KEY_SECRET;

static Ant ant = Ant();
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
    {122, 8102}, // BIKE_CADENCE
    {123, 8118}, // BIKE_SPEED
    {120, 8070} // HR_MONITOR
};

static ant_channel_status_type ant_channel_status[ANT_NUM_CHANNELS];

static void ant_handle_message();
static void ant_setup_channel(uint8_t channel, uint32_t serial_number, ant_device_type device_type);
static void ant_check_messages();
static void ant_service_data();
static void ant_parse_broadcast_data(uint8_t channel_id, uint8_t* data);
static void ant_parse_channel_event(uint8_t channel_id, uint8_t code);
static void ant_open_channel(uint8_t channel);
static void ant_fill_data(SensorData* data);

void ant_init()
{
    pinMode(ANT_RESET_PIN, OUTPUT);
    digitalWrite(ANT_RESET_PIN, HIGH);

    ANT_SERIAL_PORT.begin(BAUD_RATE);
    ANT_SERIAL_PORT.attachCts(ANT_SERIAL_PORT_CTS_PIN);
    ant.setSerial(ANT_SERIAL_PORT);

    ant_reset();
}

void ant_reset()
{
    ResetSystem rs = ResetSystem();
    ant.send(rs);
    memset(ant_channel_status, 0, sizeof(ant_channel_status));
}

void ant_tick()
{
    ant_check_messages();
    ant_service_data();
}

void ant_configure_radio(ChannelConfig* config) {
    num_active_channels = config->channel_serial_number_count;
    next_data_transmit = millis() + SAMPLE_DELAY_IN_MILLIS;
    for (uint8_t i = 0; i < config->channel_serial_number_count; i++) {
        if (config->channel_serial_number[i] != 0)
        {
            ant_setup_channel(i, config->channel_serial_number[i], (ant_device_type)config->channel_type[i]);
        }
    }
}

static void ant_check_messages()
{
    ant.readPacket();
    if (ant.getResponse().isAvailable())
    {
        ant_handle_message();
    }
    else if (ant.getResponse().isError()) {
        debug_ant_error_code(ant.getResponse().getErrorCode());
    }
}

static void ant_service_data()
{
    if (millis() >= next_data_transmit && num_active_channels != 0)
    {
        next_data_transmit += SAMPLE_DELAY_IN_MILLIS;
        SensorData data = SensorData_init_default;
        ant_fill_data(&data);
        debug_ant_data_sent(&data);
        xbee_send_data(&data);
    }
}

static void ant_setup_channel(uint8_t channel, uint32_t serial_number, ant_device_type device_type)
{
    AssignChannel ac;
    ChannelId ci;
    ChannelPeriod cp;
    ChannelRfFrequency crf;

    debug_ant_config_channel(channel, (uint16_t)(serial_number & 0xFFFF), device_type);

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
    debug_ant_response(ant.getResponse());
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
        case RESPONSE_NO_ERROR:
        case EVENT_RX_FAIL:
            break;

        case EVENT_RX_SEARCH_TIMEOUT:
            // send message back to server (once error reporting implemented) that sensor was lost and retry
            ant_open_channel(channel_id);
            break;

        case EVENT_CHANNEL_CLOSED:
            break;

        default:
            break;
    }
}

static void ant_fill_data(SensorData* data)
{
    for (uint8_t i = 0; i < num_active_channels; i++)
    {
        data->channel_counts[i] = ant_channel_status[i].current_count;
        ant_channel_status[i].current_count = 0;
        data->channel_state[i] = ant_channel_status[i].active ? SensorData_ConnnectionState_CONNECTED : SensorData_ConnnectionState_DISCONNECTED;
    }
    data->channel_counts_count = num_active_channels;
    data->channel_state_count = num_active_channels;
}