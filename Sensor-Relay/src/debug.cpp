#include <Arduino.h>
#include "defines.h"
#include "debug.h"

#if (DEBUG_ENABLED)

#define DEBUG_STARTUP_DELAY 5000

static void debug_ant_event_message(uint8_t code);

void debug_init()
{
    delay(DEBUG_STARTUP_DELAY);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    DEBUG_SERIAL_PORT.begin(BAUD_RATE);
    DEBUG_SERIAL_PORT.println("System Init");
}

void debug_tick()
{
    while (DEBUG_SERIAL_PORT.available())
    {
        DEBUG_SERIAL_PORT.read();
    }
}

void debug_ant_response(AntResponse message)
{
    uint8_t msgId = message.getMsgId();
    switch (msgId) {
        case CHANNEL_EVENT:
        {
            ChannelEventResponse cer = ChannelEventResponse();
            message.getChannelEventResponseMsg(cer);
            DEBUG_SERIAL_PORT.println("Received Msg: ChannelEventResponse");
            DEBUG_SERIAL_PORT.print("Channel: ");
            DEBUG_SERIAL_PORT.println(cer.getChannelNumber());
            debug_ant_event_message(cer.getCode());
            break;
        }

        case START_UP_MESSAGE:
        {
            StartUpMessage sum = StartUpMessage();
            message.getStartUpMsg(sum);
            DEBUG_SERIAL_PORT.println("Received Msg: StartupMessage");
            DEBUG_SERIAL_PORT.print("Message: ");
            DEBUG_SERIAL_PORT.println(sum.getMessage());
            break;
        }

        case BROADCAST_DATA:
        {
            BroadcastData bd = BroadcastData();
            message.getBroadcastDataMsg(bd);
            DEBUG_SERIAL_PORT.println("Received Msg: BroadcastData");
            DEBUG_SERIAL_PORT.print("Channel: ");
            DEBUG_SERIAL_PORT.println(bd.getChannelNumber());
            DEBUG_SERIAL_PORT.print("Data:[");
            DEBUG_SERIAL_PORT.print(bd.getData(0), HEX);
            for (uint8_t i = 1; i < 8; i++) {
                DEBUG_SERIAL_PORT.print(", ");
                DEBUG_SERIAL_PORT.print(bd.getData(i), HEX);
            }
            DEBUG_SERIAL_PORT.println("]");
            break;
        }

        default:
            DEBUG_SERIAL_PORT.print("Undefined Message: ");
            DEBUG_SERIAL_PORT.println(msgId, HEX);
            break;
    }
}

void debug_ant_error_code(uint8_t code)
{
    DEBUG_SERIAL_PORT.print("ANT MSG ERROR: ");
    DEBUG_SERIAL_PORT.println(code);
}

void debug_ant_config_channel(uint8_t channel, uint16_t id, ant_device_type device_type)
{
    DEBUG_SERIAL_PORT.print("Configuring ANT Channel: ");
    DEBUG_SERIAL_PORT.print(channel);
    DEBUG_SERIAL_PORT.print(" ID: ");
    DEBUG_SERIAL_PORT.print(id);
    DEBUG_SERIAL_PORT.print(" TYPE: ");
    DEBUG_SERIAL_PORT.println(device_type);
}

static void debug_ant_event_message(uint8_t code)
{
    DEBUG_SERIAL_PORT.print("Code: ");
    switch (code) {
        case RESPONSE_NO_ERROR:
            DEBUG_SERIAL_PORT.println("RESPONSE_NO_ERROR");
            break;

        case EVENT_RX_FAIL:
            DEBUG_SERIAL_PORT.println("EVENT_RX_FAIL");
            break;

        case EVENT_RX_SEARCH_TIMEOUT:
            DEBUG_SERIAL_PORT.println("EVENT_RX_SEARCH_TIMEOUT");
            break;

        case EVENT_CHANNEL_CLOSED:
            DEBUG_SERIAL_PORT.println("EVENT_CHANNEL_CLOSED");
            break;

        case EVENT_CHANNEL_COLLISION:
            DEBUG_SERIAL_PORT.println("EVENT_CHANNEL_COLLISION");
            break;

        default:
            DEBUG_SERIAL_PORT.println(code);
            break;
    }
}

void debug_xbee_response(XBeeResponse message)
{
    uint8_t apiId = message.getApiId();
    DEBUG_SERIAL_PORT.print("Got XBee Message: ");
    switch (apiId){
        case ZB_RX_RESPONSE:
        {
            DEBUG_SERIAL_PORT.println("ZB_RX_RESPONSE");
            ZBRxResponse zrr = ZBRxResponse();
            message.getZBRxResponse(zrr);
            // for (uint8_t i = 0; i < 20; i++)
            // {
            //     DEBUG_SERIAL_PORT.print(buffer[i]);
            //     DEBUG_SERIAL_PORT.print(", ");
            // }
            break;
        }

        case MODEM_STATUS_RESPONSE:
        {
            ModemStatusResponse msr = ModemStatusResponse();
            message.getModemStatusResponse(msr);
            DEBUG_SERIAL_PORT.print("Modem Status: ");
            DEBUG_SERIAL_PORT.println(msr.getStatus());
    //             "HARDWARE_RESET",
    // "WATCHDOG_TIMER_RESET",
    // "ASSOCIATED",
    // "DISASSOCIATED",
    // "SYNCHRONIZATION_LOST",
    // "COORDINATOR_REALIGNMENT",
    // "COORDINATOR_STARTED"
            break;
        }

        case ZB_TX_STATUS_RESPONSE:
        {
            ZBTxStatusResponse ztsr = ZBTxStatusResponse();
            message.getZBTxStatusResponse(ztsr);
            DEBUG_SERIAL_PORT.print("Xbee Success: ");
            DEBUG_SERIAL_PORT.println(ztsr.isSuccess());
            break;
        }
        default:
        {
            DEBUG_SERIAL_PORT.println(apiId);
            break;
        }
    }
}

void debug_xbee_error_code(uint8_t code)
{
    DEBUG_SERIAL_PORT.print("XBee Error: ");
    DEBUG_SERIAL_PORT.println(code);
}

void debug_pb_incoming_data()
{
    // DEBUG_SERIAL_PORT.print("Length: ");
    // DEBUG_SERIAL_PORT.println(zrr.getDataLength());
    // DEBUG_SERIAL_PORT.print("Data: ");
    // for (uint8_t i = 0; i < zrr.getDataLength(); i++)
    // {
    //     DEBUG_SERIAL_PORT.print(zrr.getData(i));
    //     DEBUG_SERIAL_PORT.print(", ");
    // }
    // DEBUG_SERIAL_PORT.println();
    // DEBUG_SERIAL_PORT.print("Channel Type: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.channelType));
    // DEBUG_SERIAL_PORT.print("deviceNumber: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.deviceNumber));
    // DEBUG_SERIAL_PORT.print("devicetype: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.deviceType));
    // DEBUG_SERIAL_PORT.print("rfFrequency: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.rfFrequency));
    // DEBUG_SERIAL_PORT.print("channel period: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.channelPeriod));
    // DEBUG_SERIAL_PORT.print("Channel network: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.channelNetwork));
    // DEBUG_SERIAL_PORT.print("transmissionType Type: ");
    // DEBUG_SERIAL_PORT.println(zrr.getData(message.antconfig.transmissionType));
}

void debug_pb_input_error(pb_istream_t* err_stream)
{
    DEBUG_SERIAL_PORT.print("PB Error: ");
    DEBUG_SERIAL_PORT.println(PB_GET_ERROR(err_stream));
}

void debug_pb_output_error(pb_ostream_t* err_stream)
{
    DEBUG_SERIAL_PORT.print("PB Error: ");
    DEBUG_SERIAL_PORT.println(PB_GET_ERROR(err_stream));
}

void debug_ant_data_sent(SensorData* data)
{
    DEBUG_SERIAL_PORT.print("Transmitting Data, num channels: ");
    DEBUG_SERIAL_PORT.println(data->channel_counts_count);

    for (uint8_t i = 0; i < data->channel_counts_count; i++)
    {
        DEBUG_SERIAL_PORT.print("Channel: ");
        DEBUG_SERIAL_PORT.print(i);
        DEBUG_SERIAL_PORT.print(" Counts: ");
        DEBUG_SERIAL_PORT.print(data->channel_counts[i]);
        DEBUG_SERIAL_PORT.print(" Activity: ");
        DEBUG_SERIAL_PORT.println(data->channel_state[i]);
    }
}
#else
// put empty definitions here
#endif