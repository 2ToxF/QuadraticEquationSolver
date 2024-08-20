#include <stdio.h>
#include <math.h>
#include <assert.h>

enum RootsNumber
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INFINITE_NUM_OF_ROOTS,
};
enum ProgramStatus
{
    OK,
    PRINT_ROOTS_ERROR_CODE,
};

struct QuadEqParameters
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
};

void input_coefs(double* var_adress, char var_char);
void clear_buffer();
RootsNumber solve_quad_eq(struct QuadEqParameters* params);
RootsNumber solve_line_eq(struct QuadEqParameters* params);
ProgramStatus print_roots(int number, struct QuadEqParameters* roots);
bool is_zero(double x);

int main()
{
    struct QuadEqParameters quad_eq_params = {0, 0, 0, 0, 0};
    RootsNumber equation_roots_number = NO_ROOTS;
    ProgramStatus code_status = OK;

    printf("# Enter the coefficients of quadratic equation:\n");
    input_coefs(&quad_eq_params.a, 'a');
    input_coefs(&quad_eq_params.b, 'b');
    input_coefs(&quad_eq_params.c, 'c');

    equation_roots_number = solve_quad_eq(&quad_eq_params);
    code_status = print_roots(equation_roots_number, &quad_eq_params);

    return code_status;
}


void input_coefs(double* var_adress, char var_char)
{
    assert(var_adress != NULL);

    printf("# %c = ", var_char);

    while (scanf("%lf", var_adress) != 1)
    {
        clear_buffer();
        printf("Invalid value, try again\n");
        printf("# %c = ", var_char);
    }
}


void clear_buffer()
{
    while (getchar() != '\n'){}
}


RootsNumber solve_quad_eq(struct QuadEqParameters* params)
{
    double a = params->a, b = params->b, c = params->c;

    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(params != NULL);

    double D = b*b - 4*a*c;
    if (is_zero(a))
        return solve_line_eq(params);
    else if (D < 0)
        return NO_ROOTS;
    else if (is_zero(D))
    {
        params->x1 = -b/(2*a);
        return ONE_ROOT;
    }
    else
    {
        params->x1 = (-b - sqrt(D))/(2*a);
        params->x2 = (-b + sqrt(D))/(2*a);
        return TWO_ROOTS;
    }
}


RootsNumber solve_line_eq(struct QuadEqParameters* params)
{
    double b = params->b, c = params->c;

    assert(std::isfinite(b));
    assert(std::isfinite(c));
    assert(params != NULL);

    if (is_zero(b))
    {
        if (is_zero(c))
            return INFINITE_NUM_OF_ROOTS;
        else
            return NO_ROOTS;
    }
    else
    {
        params->x1 = -c/b;
        return ONE_ROOT;
    }
}


ProgramStatus print_roots(int number, struct QuadEqParameters* roots)
{
    assert(std::isfinite(number));
    assert(roots != NULL);

    if (is_zero(roots->x1))
        roots->x1 = 0.0;
    if (is_zero(roots->x2))
        roots->x2 = 0.0;

    switch (number)
    {
        case NO_ROOTS:
        {
            printf("This equation has no real roots\n");
            return OK;
        }
        case ONE_ROOT:
        {
            printf("This equation has only one real root: %.2f\n", roots->x1);
            return OK;
        }
        case TWO_ROOTS:
        {
            printf("This equation has only two real roots: %.2f; %.2f\n", roots->x1, roots->x2);
            return OK;
        }
        case INFINITE_NUM_OF_ROOTS:
        {
            printf("This equation has an infinite number of real roots\n");
            return OK;
        }
        default:
        {
            printf("Unknown error:\n"
                   "In function print_roots(): variable number = %d is invalid\n", number);
            return PRINT_ROOTS_ERROR_CODE;
        }
    }
}


bool is_zero(double x)
{
    assert(std::isfinite(x));
    return abs(x) <= 0.1E-7;
}
