#include "cmd_processing.h"
#include "io.h"
#include "tests.h"

CodeStatus run_program(CmdOption option);

int main(int argc, const char* argv[])
{
    CmdOption option = cmd_read(argc, argv);
    return run_program(option);
}


CodeStatus run_program(CmdOption option)
{
    CodeStatus code_status = OK;

    if (option == SOLVE)
        code_status = run_main_solve();

    else if (option == TEST)
        code_status = run_main_test();

    else if (option == HELP)
    {
        print_help();
        code_status = OK;
    }

    else
    {
        printf("error: unknown option");
        print_help();
        code_status = PROGRAM_NOT_STARTED;
    }

    print_code_status(code_status);
    return code_status;
}
