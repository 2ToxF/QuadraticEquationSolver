#include <stdio.h>
#include <cstring>
#include "tests.h"
#include "quad.h"
#include "cmd_processing.h"

static const char* const TEST_FLAG = "--tests";
static const char* const SOLVE_FLAG = "--solve";
static const char* const HELP_FLAG = "--help";
static const int NO_FLAGS = 1;


CmdOption cmd_read(int option_number, const char* options[])
{
    if (option_number == 1)
        return SOLVE;
    else if (option_number == 3)
        return UNKNOWN;
    else if (strcmp(options[1], SOLVE_FLAG) == 0)
        return SOLVE;
    else if (strcmp(options[1], TEST_FLAG) == 0)
        return TEST;
    else if (strcmp(options[1], HELP_FLAG) == 0)
        return HELP;
    else
        return UNKNOWN;
}
