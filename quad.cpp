#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "quad.h"
#include "tests.h"

static CodeStatus isfinite_check(double x);
static CodeStatus solve_line_eq(struct QuadEqParameters* params);


static CodeStatus isfinite_check(double x)
{
    if (isfinite(x))
        return OK;
    else
        return NUMBER_IS_INFINITE_ERROR;
}


bool is_zero(double x)
{
    return abs(x) <= 1E-7;
}


CodeStatus run_main_solve()
{
    struct QuadEqParameters quad_eq_params = {};
    CodeStatus code_status = OK;

    PRINTPURPLE("# Enter the coefficients of quadratic equation (or \"exit\" to exit the program):\n");

    if (input_all_coeffs(&quad_eq_params) == EXIT)
        return code_status;

    code_status = solve_quad_eq(&quad_eq_params);
    if (code_status != OK)
        return code_status;
    print_roots(&quad_eq_params);
    return code_status;
}


static CodeStatus solve_line_eq(struct QuadEqParameters* params)
{
    assert(params != NULL);

    CodeStatus code_status = OK;
    if ((code_status = isfinite_check(params->b)) != OK)
        return print_infinite_error("b");
    if ((code_status = isfinite_check(params->c)) != OK)
        return print_infinite_error("c");

    double b = params->b, c = params->c;

    if (is_zero(b))
    {
        if (is_zero(c))
        {
            params->roots_number = INFINITE_NUM_OF_ROOTS;
            return code_status;
        }
        else
        {
            params->roots_number = NO_ROOTS;
            return code_status;
        }
    }
    else
    {
        params->x1 = -c/b;
        params->roots_number = ONE_ROOT;
        return code_status;
    }
}


CodeStatus solve_quad_eq(struct QuadEqParameters* params)
{
    assert(params != NULL);

    CodeStatus code_status = OK;
    if ((code_status = isfinite_check(params->a)) != OK)
        return print_infinite_error("a");
    if ((code_status = isfinite_check(params->b)) != OK)
        return print_infinite_error("b");
    if ((code_status = isfinite_check(params->c)) != OK)
        return print_infinite_error("c");

    double a = params->a, b = params->b, c = params->c;

    double discr = b*b - 4*a*c;
    if (is_zero(a))
        return solve_line_eq(params);
    else if (discr < 0)
    {
        params->roots_number = NO_ROOTS;
        return code_status;
    }
    else if (is_zero(discr))
    {
        params->x1 = -b/(2*a);
        params->roots_number = ONE_ROOT;
        return code_status;
    }
    else
    {
        params->x1 = (-b - sqrt(discr))/(2*a);
        params->x2 = (-b + sqrt(discr))/(2*a);
        params->roots_number = TWO_ROOTS;
        return code_status;
    }
}
