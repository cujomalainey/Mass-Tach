/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Sat Dec 31 20:37:06 2016. */

#include "SensorData.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t ChannelConfig_fields[3] = {
    PB_FIELD(  1, INT32   , REPEATED, STATIC  , FIRST, ChannelConfig, channel_serial_number, channel_serial_number, 0),
    PB_FIELD(  2, UENUM   , REPEATED, STATIC  , OTHER, ChannelConfig, channel_type, channel_serial_number, 0),
    PB_LAST_FIELD
};

const pb_field_t SensorData_fields[3] = {
    PB_FIELD(  1, INT32   , REPEATED, STATIC  , FIRST, SensorData, channel_counts, channel_counts, 0),
    PB_FIELD(  2, UENUM   , REPEATED, STATIC  , OTHER, SensorData, channel_state, channel_counts, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */
