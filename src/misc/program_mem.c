#include "program_mem.h"

typedef union _TS_PROGRAM_TAG {
    TS_PROGRAM program;
    TS_STREAM stream;
} TS_PROGRAM_TAG;

static TS_PROGRAM_TAG programMEM[MAX_PID+1] = {0,};

TS_PROGRAM* reset_ProgramMem(u_int PMT_PID, u_int program_number) {
    TS_PROGRAM* program = get_ProgramFromMem(PMT_PID);
    TS_STREAM* next = program->stream;
    while (next) {
        TS_STREAM* current = next;
        next = current->next;
		memset(&programMEM[current->elementary_PID], 0, sizeof(*programMEM));
    }
    memset(&programMEM[PMT_PID], 0, sizeof(*programMEM));
    program->PMT_PID = PMT_PID;
    program->program_number = program_number;
    return program;
}

TS_PROGRAM* get_ProgramFromMem(u_int PMT_PID) {
    return &programMEM[PMT_PID].program;
}

TS_STREAM* store_StreamToMem(TS_PROGRAM* program, u_int elementary_PID, u_int stream_type) {
    TS_STREAM** current = &program->stream;
    while (*current) {
      if ((*current)->elementary_PID == elementary_PID) { break; }
      current = &(*current)->next;
    }
    if (!*current) { *current = get_StreamFromMem(elementary_PID); }
    memset(&programMEM[elementary_PID], 0, sizeof(*programMEM));
    (*current)->stream_type = stream_type;
    (*current)->elementary_PID = elementary_PID;
    (*current)->program = program;
    return *current;
}

TS_STREAM* get_StreamFromMem(u_int elementary_PID) {
    return &programMEM[elementary_PID].stream;
}
