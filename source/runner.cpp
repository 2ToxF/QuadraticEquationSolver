/*!
    \file
    File with the main program runner function
*/

#include "cmd_processing.h"
#include "errors.h"
#include "input_output.h"
#include "quad.h"
#include "runner.h"
#include "tests.h"


CodeError run_program(CmdOption option)
{
    CodeError code_status = NO_ERROR;

    if (option == SOLVE)
        code_status = run_main_solve();

    else if (option == TEST)
        code_status = run_main_test();

    else if (option == HELP)
    {
        print_help();
        code_status = NO_ERROR;
    }

    else
    {
        PRINTRED("error: unknown option");
        print_help();
        code_status = PROGRAM_NOT_STARTED;
    }

    print_code_status(code_status);
    return code_status;
}
