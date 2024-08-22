#ifndef CMD_PROCESSING_H
#define CMD_PROCESSING_H

#include "quad.h"

enum cmdOption
{
    TEST,
    SOLVE,
    HELP,
    UNKNOWN,
};

cmdOption cmd_read(int argc, const char* argv[]);
CodeStatus run_program(cmdOption option, const char* argv[]);

#endif
