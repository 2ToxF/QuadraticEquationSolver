#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "tests.h"
#include "quad.h"

static InputStatus clear_buffer();
static CodeStatus isfinite_check(double x);
static bool is_zero(double x);
static CodeStatus print_infinite_error(const char var[]);
static CodeStatus solve_line_eq(struct QuadEqParameters* params);


static InputStatus clear_buffer()
{
    InputStatus input_status = EXIT;
    char input_string[100] = {};
    const char exit_string[5] = "exit";

    int i = 0;
    while ((input_string[i] = (char) getchar()) != '\n')
        i++;

    if (i == 4)
    {
        for (int j = 0; j < 4; j++)
        {
            if (input_string[j] != exit_string[j])
                input_status = CONTINUE;
        }
    }
    else
        input_status = CONTINUE;

    return input_status;
}


InputStatus input_coeff(double* var_adress, char var_char)
{
    assert(var_adress != NULL);

    printf("# %c = ", var_char);

    while (scanf("%lf", var_adress) != 1)
    {
        if (clear_buffer() == EXIT)
        {
            printf("End of the program");
            return EXIT;
        }
        printf("Invalid value, try again\n");
        printf("# %c = ", var_char);
    }

    return CONTINUE;
}


static CodeStatus isfinite_check(double x)
{
    if (isfinite(x))
        return OK;
    else
        return NUMBER_IS_INFINITE_ERROR;
}


static bool is_zero(double x)
{
    return abs(x) <= 1E-7;
}


static CodeStatus print_infinite_error(const char var[])
{
    printf("error:\n"
          "value of variable %s is infinite", var);
    return NUMBER_IS_INFINITE_ERROR;
}


void print_roots(struct QuadEqParameters* roots)
{
    assert(roots != NULL);

    if (is_zero(roots->x1))
        roots->x1 = 0.0;
    if (is_zero(roots->x2))
        roots->x2 = 0.0;

    switch (roots->roots_number)
    {
        case NO_ROOTS:
        {
            printf("This equation has no real roots\n");
            break;
        }
        case ONE_ROOT:
        {
            printf("This equation has only one real root: %.2lg\n", roots->x1);
            break;
        }
        case TWO_ROOTS:
        {
            printf("This equation has only two real roots: %.2lg; %.2lg\n", roots->x1, roots->x2);
            break;
        }
        case INFINITE_NUM_OF_ROOTS:
        {
            printf("This equation has an infinite number of real roots\n");
            break;
        }
        default:
        {
            printf("print_roots(): default situation");
            break;
        }
    }
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
