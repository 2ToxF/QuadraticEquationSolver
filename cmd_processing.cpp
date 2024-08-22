#include <stdio.h>
#include <string.h>
#include "cmd_processing.h"
#include "quad.h"
#include "tests.h"

static const char* const TEST_FLAG = "--tests";
static const char* const SOLVE_FLAG = "--solve";
static const char* const HELP_FLAG = "--help";
static const int INPUT_FLAG_NUM = 1;
enum OptionNumber
{
    ONE_OPTION=1,
    TWO_OPTIONS,
};


CmdOption cmd_read(int option_number, const char* options[])
{
    switch (option_number)
    {
        case ONE_OPTION:
            return SOLVE;
        case TWO_OPTIONS:
        {
            if (strcmp(options[INPUT_FLAG_NUM], SOLVE_FLAG) == 0)
            {
                return SOLVE;
            }
            else if (strcmp(options[INPUT_FLAG_NUM], TEST_FLAG) == 0)
            {
                return TEST;
            }
            else if (strcmp(options[INPUT_FLAG_NUM], HELP_FLAG) == 0)
            {
                return HELP;
            }
            else
            {
                return UNKNOWN;
            }
        }
        default:
            return UNKNOWN;
    }
}
