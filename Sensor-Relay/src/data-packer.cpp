#include <pb_common.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "data-packer.h"

// SensorMessage message = SensorMessage_init_default;
// static uint8_t sensorDataBuffer[64];
// pb_istream_t stream;

    // stream = pb_ostream_from_buffer(sensorDataBuffer, sizeof(sensorDataBuffer));
    // pb_encode(&stream, SensorData_fields, &message);

            // uint8_t buffer[40];
            // pb_ostream_t strm = pb_ostream_from_buffer(buffer, 40);
            // message.msg_type = SensorMessage_MessageType_CHANNEL_CONFIG;
            // message.antconfig.channelType = 22;
            // message.antconfig.deviceNumber = 650;
            // message.antconfig.deviceType = 120;
            // message.antconfig.transmissionType = 0;
            // message.antconfig.channelPeriod = 8040;
            // message.antconfig.rfFrequency = 57;
            // message.antconfig.channelNetwork = 0;
            // xbee.getResponse().getZBRxResponse(zrr);
            // pb_encode(&strm, SensorMessage_fields, &message);

            // stream = pb_istream_from_buffer(buffer, 20);
            // if (!pb_decode(&stream, SensorMessage_fields, &message))
            // {
            //     DEBUG_SERIAL_PORT.println("Decoding Failed");
            // }

// message.distance.funcs.decode  = &decode_distance;