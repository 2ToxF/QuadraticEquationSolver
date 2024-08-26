/*!
    \file
    File with code for solving quadratic equation and input coefficients of it
*/

#include <math.h>
#include "errors.h"
#include "input_output.h"
#include "quad.h"
#include "utils.h"

/*!
    Solves linear equation (a = 0)
    \param[in, out]  params  Parameters for equation
    \return Status of completing the program
*/
static CodeError solve_line_eq(struct QuadEqParameters* params);

/*!
    Solves quadratic equation (a != 0)
    \param[in, out]  params  Parameters for equation
    \return Status of completing the program
*/
static CodeError solve_quad_eq(struct QuadEqParameters* params);


CodeError main_eq_solve(struct QuadEqParameters* params)
{
    ASSERT(params != NULL);

    CodeError code_status = NO_ERROR;
    if ((code_status = isfinite_check(params->a)) != NO_ERROR)
        return code_status;
    if ((code_status = isfinite_check(params->b)) != NO_ERROR)
        return code_status;
    if ((code_status = isfinite_check(params->c)) != NO_ERROR)
        return code_status;

    if (is_zero(params->a))
        return solve_line_eq(params);
    else
        return solve_quad_eq(params);
}


CodeError run_main_solve()
{
    struct QuadEqParameters quad_eq_params = {};
    CodeError code_status = NO_ERROR;

    PRINTPURPLE("# Enter the coefficients of quadratic equation (or \"exit\" to exit the program):\n");

    if (input_all_coeffs(&quad_eq_params) == EXIT)
        return code_status;

    code_status = main_eq_solve(&quad_eq_params);
    if (code_status != NO_ERROR)
        return code_status;

    print_roots(&quad_eq_params);

    return code_status;
}


static CodeError solve_line_eq(struct QuadEqParameters* params)
{
    ASSERT(params != NULL);

    CodeError code_status = NO_ERROR;
    if ((code_status = isfinite_check(params->b)) != NO_ERROR)
        return code_status;
    if ((code_status = isfinite_check(params->c)) != NO_ERROR)
        return code_status;

    double b = params->b, c = params->c;

    if (is_zero(b))
    {
        if (is_zero(c))
        {
            params->roots_number = INFINITE_NUM_OF_ROOTS;
        }
        else
        {
            params->roots_number = NO_ROOTS;
        }
    }
    else
    {
        params->x1 = -c/b;
        params->roots_number = ONE_ROOT;
    }

    return code_status;
}


static CodeError solve_quad_eq(struct QuadEqParameters* params)
{
    ASSERT(params != NULL);

    CodeError code_status = NO_ERROR;
    if ((code_status = isfinite_check(params->a)) != NO_ERROR)
        return code_status;
    if ((code_status = isfinite_check(params->b)) != NO_ERROR)
        return code_status;
    if ((code_status = isfinite_check(params->c)) != NO_ERROR)
        return code_status;

    double a = params->a, b = params->b, c = params->c;

    if (is_zero(b))
    {
        if (is_zero(c))
        {
            params->x1 = 0;
            params->roots_number = ONE_ROOT;
        }
        else
        {
            params->x1 =  sqrt(-c/a);
            params->x1 = -sqrt(-c/a);
            params->roots_number = TWO_ROOTS;
        }
    }
    else if (is_zero(c))
    {
        params->x1 = 0;
        params->x2 = -b/a;
        if (params->x1 > params->x2)
            swap(&params->x1, &params->x2, sizeof(double));
        params->roots_number = TWO_ROOTS;
    }
    else
    {
        double discr = b*b - 4*a*c;

        if (discr < 0)
        {
            params->roots_number = NO_ROOTS;
        }
        else if (is_zero(discr))
        {
            params->x1 = -b/(2*a);
            params->roots_number = ONE_ROOT;
        }
        else
        {
            params->x1 = (-b - sqrt(discr))/(2*a);
            params->x2 = (-b + sqrt(discr))/(2*a);
            if (params->x1> params->x2)
                swap(&params->x1, &params->x2, sizeof(double));
            params->roots_number = TWO_ROOTS;
        }
    }

    return NO_ERROR;
}
