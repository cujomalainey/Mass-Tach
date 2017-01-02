#include <ANT.h>
#include <XBee.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "SensorData.pb.h"
#include "ant-controller.h"

void debug_init();
void debug_tick();

void debug_ant_response(AntResponse message);
void debug_ant_error_code(uint8_t code);
void debug_ant_config_channel(uint8_t channel, uint16_t id, ant_device_type device_type);
void debug_ant_data_sent(SensorData* data);

void debug_xbee_response(XBeeResponse message);
void debug_xbee_error_code(uint8_t code);

void debug_pb_input_error(pb_istream_t* err_stream);
void debug_pb_output_error(pb_ostream_t* err_stream);