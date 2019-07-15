/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.9.3 at Sun Jul 14 22:19:04 2019. */

#ifndef PB_MESSAGES_PB_H_INCLUDED
#define PB_MESSAGES_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _AssignCommand {
    char dummy_field;
/* @@protoc_insertion_point(struct:AssignCommand) */
} AssignCommand;

typedef struct _IdentifyCommand {
    char dummy_field;
/* @@protoc_insertion_point(struct:IdentifyCommand) */
} IdentifyCommand;

typedef struct _RequestStatusCommand {
    char dummy_field;
/* @@protoc_insertion_point(struct:RequestStatusCommand) */
} RequestStatusCommand;

typedef struct _ScanCommand {
    char dummy_field;
/* @@protoc_insertion_point(struct:ScanCommand) */
} ScanCommand;

typedef struct _SensorCountStatus {
    char dummy_field;
/* @@protoc_insertion_point(struct:SensorCountStatus) */
} SensorCountStatus;

typedef struct _SetCountRateCommand {
    char dummy_field;
/* @@protoc_insertion_point(struct:SetCountRateCommand) */
} SetCountRateCommand;

typedef struct _SystemBootStatus {
    char dummy_field;
/* @@protoc_insertion_point(struct:SystemBootStatus) */
} SystemBootStatus;

typedef struct _SystemFaultStatus {
    char dummy_field;
/* @@protoc_insertion_point(struct:SystemFaultStatus) */
} SystemFaultStatus;

typedef struct _SystemStatus {
    char dummy_field;
/* @@protoc_insertion_point(struct:SystemStatus) */
} SystemStatus;

typedef struct _TombStoneStatus {
    char dummy_field;
/* @@protoc_insertion_point(struct:TombStoneStatus) */
} TombStoneStatus;

typedef struct _Command {
    pb_size_t which_type;
    union {
        ScanCommand scan;
        AssignCommand assign;
        RequestStatusCommand request;
        IdentifyCommand identify;
        SetCountRateCommand countRate;
    } type;
/* @@protoc_insertion_point(struct:Command) */
} Command;

typedef struct _Status {
    pb_size_t which_type;
    union {
        SystemStatus system;
        SensorCountStatus count;
        SystemFaultStatus fault;
        SystemBootStatus boot;
        TombStoneStatus tomb;
    } type;
/* @@protoc_insertion_point(struct:Status) */
} Status;

/* Default values for struct fields */

/* Initializer values for message structs */
#define ScanCommand_init_default                 {0}
#define AssignCommand_init_default               {0}
#define RequestStatusCommand_init_default        {0}
#define IdentifyCommand_init_default             {0}
#define SetCountRateCommand_init_default         {0}
#define Command_init_default                     {0, {ScanCommand_init_default}}
#define SystemStatus_init_default                {0}
#define SensorCountStatus_init_default           {0}
#define SystemFaultStatus_init_default           {0}
#define SystemBootStatus_init_default            {0}
#define TombStoneStatus_init_default             {0}
#define Status_init_default                      {0, {SystemStatus_init_default}}
#define ScanCommand_init_zero                    {0}
#define AssignCommand_init_zero                  {0}
#define RequestStatusCommand_init_zero           {0}
#define IdentifyCommand_init_zero                {0}
#define SetCountRateCommand_init_zero            {0}
#define Command_init_zero                        {0, {ScanCommand_init_zero}}
#define SystemStatus_init_zero                   {0}
#define SensorCountStatus_init_zero              {0}
#define SystemFaultStatus_init_zero              {0}
#define SystemBootStatus_init_zero               {0}
#define TombStoneStatus_init_zero                {0}
#define Status_init_zero                         {0, {SystemStatus_init_zero}}

/* Field tags (for use in manual encoding/decoding) */
#define Command_scan_tag                         1
#define Command_assign_tag                       2
#define Command_request_tag                      3
#define Command_identify_tag                     4
#define Command_countRate_tag                    5
#define Status_system_tag                        1
#define Status_count_tag                         2
#define Status_fault_tag                         3
#define Status_boot_tag                          4
#define Status_tomb_tag                          5

/* Struct field encoding specification for nanopb */
extern const pb_field_t ScanCommand_fields[1];
extern const pb_field_t AssignCommand_fields[1];
extern const pb_field_t RequestStatusCommand_fields[1];
extern const pb_field_t IdentifyCommand_fields[1];
extern const pb_field_t SetCountRateCommand_fields[1];
extern const pb_field_t Command_fields[6];
extern const pb_field_t SystemStatus_fields[1];
extern const pb_field_t SensorCountStatus_fields[1];
extern const pb_field_t SystemFaultStatus_fields[1];
extern const pb_field_t SystemBootStatus_fields[1];
extern const pb_field_t TombStoneStatus_fields[1];
extern const pb_field_t Status_fields[6];

/* Maximum encoded size of messages (where known) */
#define ScanCommand_size                         0
#define AssignCommand_size                       0
#define RequestStatusCommand_size                0
#define IdentifyCommand_size                     0
#define SetCountRateCommand_size                 0
#define Command_size                             2
#define SystemStatus_size                        0
#define SensorCountStatus_size                   0
#define SystemFaultStatus_size                   0
#define SystemBootStatus_size                    0
#define TombStoneStatus_size                     0
#define Status_size                              2

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define MESSAGES_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
