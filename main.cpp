#include <stdio.h>
#include "tests.h"
#include "quad.h"

//#define TEST

int main()
{
#ifdef TEST
    CodeStatus code_status = OK;
    code_status = run_all_tests();
    return code_status;
#else
    struct QuadEqParameters quad_eq_params = {};
    CodeStatus code_status = OK;

    printf("# Enter the coefficients of quadratic equation (or \"exit\" to exit the program:\n");
    if (input_coeff(&quad_eq_params.a, 'a') == EXIT)
        return code_status;
    if (input_coeff(&quad_eq_params.b, 'b') == EXIT)
        return code_status;
    if (input_coeff(&quad_eq_params.c, 'c') == EXIT)
        return code_status;

    code_status = solve_quad_eq(&quad_eq_params);
    if (code_status != OK)
        return code_status;
    print_roots(&quad_eq_params);
    return code_status;
#endif
}
