#ifndef __PROGRAM_MEM
#define __PROGRAM_MEM

#include "dvbsnoop.h"

typedef struct _TS_PROGRAM TS_PROGRAM;
typedef struct _TS_STREAM TS_STREAM;


typedef struct _TS_STREAM {
    u_int elementary_PID;
    u_int stream_type;
    TS_PROGRAM* program;
    TS_STREAM* next;
} TS_STREAM;

typedef struct _TS_PROGRAM {
    u_int PMT_PID;
    u_int program_number;
    TS_STREAM* stream;
} TS_PROGRAM;

TS_PROGRAM* reset_ProgramMem(u_int PMT_PID, u_int program_number);
TS_PROGRAM* get_ProgramFromMem(u_int PMT_PID);
TS_STREAM* store_StreamToMem(TS_PROGRAM* program, u_int elementary_PID, u_int stream_type);
TS_STREAM* get_StreamFromMem(u_int elementary_PID);

#endif
