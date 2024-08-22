#include <stdio.h>
#include <cstring>
#include "tests.h"
#include "quad.h"
#include "cmd_processing.h"

static const char* const TEST_FLAG = "--tests";
static const char* const SOLVE_FLAG = "--solve";
static const char* const HELP_FLAG = "--help";
static const int NO_FLAGS = 1;


cmdOption cmd_read(int argc, const char* argv[])
{
    if (argc == 1)
        return SOLVE;
    else if (argc == 3)
        return UNKNOWN;
    else if (strcmp(argv[1], SOLVE_FLAG) == 0)
        return SOLVE;
    else if (strcmp(argv[1], TEST_FLAG) == 0)
        return TEST;
    else if (strcmp(argv[1], HELP_FLAG) == 0)
        return HELP;
    else
        return UNKNOWN;
}


CodeStatus run_program(cmdOption option, const char* argv[])
{
    if (option == SOLVE)
    {
        struct QuadEqParameters quad_eq_params = {};
        CodeStatus code_status = OK;

        printf("# Enter the coefficients of quadratic equation (or \"exit\" to exit the program):\n");

        if (input_all_coeffs(&quad_eq_params) == EXIT)
            return code_status;

        code_status = solve_quad_eq(&quad_eq_params);
        if (code_status != OK)
            return code_status;
        print_roots(&quad_eq_params);
        return code_status;
    }

    else if (option == TEST)
    {
        CodeStatus code_status = OK;
        code_status = run_all_tests();
        return code_status;
    }

    else if (option == HELP)
    {
        printf("\nUsage: ./qe_solver.exe [option]  ||  make run\n"
               "Options:\n"
               "    --tests                      Run tests for quadratic_equation_solver\n"
               "    --solve                      Run quadratic_equation_solver\n");
        return OK;
    }

    else
    {
        printf("error: %s: unknown option", argv[1]);
        return PROGRAM_NOT_STARTED;
    }
}
