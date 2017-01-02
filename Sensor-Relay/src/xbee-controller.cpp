#include <Arduino.h>
#include <XBee.h>
#include <pb_decode.h>
#include <pb_common.h>
#include "SensorData.pb.h"
#include "defines.h"
#include "xbee-controller.h"
#include "debug.h"
#include "ant-controller.h"

/*
 * XBee Defines
 */
#define XBEE_CONTROLLER_UPPER_ADDR 0x00000000
#define XBEE_CONTROLLER_LOWER_ADDR 0x00000000

#define XBEE_OUTPUT_BUFFER_SIZE 100

static uint8_t modem_status = DISASSOCIATED;

// set up a new serial object
XBee xbee = XBee();

// SH + SL Address of receiving XBee
XBeeAddress64 coordinator = XBeeAddress64(XBEE_CONTROLLER_UPPER_ADDR, XBEE_CONTROLLER_LOWER_ADDR);

void xbee_init()
{
    XBEE_SERIAL_PORT.begin(BAUD_RATE);
    xbee.begin(XBEE_SERIAL_PORT);

    pinMode(XBEE_RESET_PIN, OUTPUT);
    digitalWrite(XBEE_RESET_PIN, HIGH);
}

void xbee_reset()
{
    digitalWrite(XBEE_RESET_PIN, LOW);
    digitalWrite(XBEE_RESET_PIN, HIGH);
}

void xbee_handle_message()
{
    debug_xbee_response(xbee.getResponse());
    uint8_t apiId = xbee.getResponse().getApiId();
    switch (apiId){
        case ZB_RX_RESPONSE:
        {
            ZBRxResponse zrr = ZBRxResponse();
            xbee.getResponse().getZBRxResponse(zrr);
            ChannelConfig message = ChannelConfig_init_default;
            pb_istream_t stream = pb_istream_from_buffer(zrr.getData(), zrr.getDataLength());
            if (pb_decode(&stream, ChannelConfig_fields, &message))
            {
                ant_configure_radio(&message);
            }
            else
            {
                debug_pb_input_error(&stream);
            }
            break;
        }

        case MODEM_STATUS_RESPONSE:
        {
            ModemStatusResponse msr = ModemStatusResponse();
            xbee.getResponse().getModemStatusResponse(msr);
            modem_status = msr.getStatus();
            break;
        }

        case ZB_TX_STATUS_RESPONSE:
        {
            ZBTxStatusResponse ztsr = ZBTxStatusResponse();
            xbee.getResponse().getZBTxStatusResponse(ztsr);
            break;
        }
        default:
        {
            break;
        }
    }
}

void xbee_tick()
{
    xbee.readPacket();
    if (xbee.getResponse().isAvailable())
    {
        xbee_handle_message();
    }
    else if (xbee.getResponse().isError()) {
        debug_xbee_error_code(xbee.getResponse().getErrorCode());
    }
}

void xbee_send_data(SensorData* data)
{
    uint8_t buffer[XBEE_OUTPUT_BUFFER_SIZE];
    pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if (pb_encode(&stream, SensorData_fields, data))
    {
        ZBTxRequest tx;
        tx.setAddress64(coordinator);
        tx.setAddress16(ZB_BROADCAST_ADDRESS);
        tx.setPayload(buffer, stream.bytes_written);
        xbee.send(tx);
    }
    else
    {
        debug_pb_output_error(&stream);
    }
}
