#include "tests.h"
#include "cmd_processing.h"

CodeStatus print_help();
CodeStatus run_main_solve();
CodeStatus run_main_test();
CodeStatus run_program(CmdOption option);

int main(int argc, const char* argv[])
{
    CmdOption option = cmd_read(argc, argv);
    return run_program(option);
}


CodeStatus print_help()
{
    printf("\nUsage: ./qe_solver.exe [option]  ||  make run\n"
            "Options:\n"
            "    --tests                      Run tests for quadratic_equation_solver\n"
            "    --solve                      Run quadratic_equation_solver\n");
    return OK;
}


CodeStatus run_main_solve()
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


CodeStatus run_main_test()
{
    CodeStatus code_status = OK;
    code_status = run_all_tests();
    return code_status;
}


CodeStatus run_program(CmdOption option)
{
    if (option == SOLVE)
        return run_main_solve();

    else if (option == TEST)
        return run_main_test();

    else if (option == HELP)
        return print_help();

    else
    {
        printf("error: unknown option");
        return print_help();
    }
}
