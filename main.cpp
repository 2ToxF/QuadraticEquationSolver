#include "cmd_processing.h"

int main(int argc, const char* argv[])
{
    cmdOption option = cmd_read(argc, argv);
    return run_program(option, argv);
}
