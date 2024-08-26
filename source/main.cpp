/*!
    \author Toxic
    \version 5.0
    \date 08.23.2024
*/

#include "cmd_processing.h"
#include "runner.h"


int main(int argc, const char* argv[])
{
    CmdOption option = cmd_read(argc, argv);
    return run_program(option);
}
