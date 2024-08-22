#ifndef CMD_PROCESSING_H
#define CMD_PROCESSING_H

#include "quad.h"

enum CmdOption
{
    TEST,
    SOLVE,
    HELP,
    UNKNOWN,
};

CmdOption cmd_read(int options_number, const char* options[]);

#endif
