#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "io.h"
#include "quad.h"
#include "tests.h"
#include "utils.h"

static CodeStatus solve_line_eq(struct QuadEqParameters* params);


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
    ASSERT(params != NULL);

    CodeStatus code_status = OK;
    if ((code_status = isfinite_check(params->b)) != OK)
        return code_status;
    if ((code_status = isfinite_check(params->c)) != OK)
        return code_status;

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
    ASSERT(params != NULL);

    CodeStatus code_status = OK;
    if ((code_status = isfinite_check(params->a)) != OK)
        return code_status;
    if ((code_status = isfinite_check(params->b)) != OK)
        return code_status;
    if ((code_status = isfinite_check(params->c)) != OK)
        return code_status;

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
        if (params->x1> params->x2)
            swap(&params->x1, &params->x2, sizeof(double));
        params->roots_number = TWO_ROOTS;
        return code_status;
    }
}
