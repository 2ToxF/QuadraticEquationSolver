#include <stdio.h>
#include <math.h>
#include <assert.h>

#define TEST

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
    TEST_FAILED_ERROR=1,
    NUMBER_IS_INFINITE_ERROR=1,
};

struct QuadEqParameters
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    RootsNumber roots_number;
};

ProgramStatus run_all_tests();
void clear_buffer();
ProgramStatus print_infinite_error(const char var[]);
ProgramStatus print_test_result(int test_number, struct QuadEqParameters* params, struct QuadEqParameters* expected_roots);
void input_coeff(double* var_adress, char var_char);
bool is_equal(double x, double y);
ProgramStatus isfinite_check(double x);
bool is_zero(double x);
ProgramStatus print_roots(struct QuadEqParameters* roots);
ProgramStatus solve_line_eq(struct QuadEqParameters* params);
ProgramStatus solve_quad_eq(struct QuadEqParameters* params);
ProgramStatus run_test(int test_number, struct QuadEqParameters* params);

int main()
{
#ifdef TEST
    ProgramStatus code_status = OK;
    code_status = run_all_tests();
    return code_status;
#else
    struct QuadEqParameters quad_eq_params = {};
    ProgramStatus code_status = OK;

    printf("# Enter the coefficients of quadratic equation:\n");
    input_coeff(&quad_eq_params.a, 'a');
    input_coeff(&quad_eq_params.b, 'b');
    input_coeff(&quad_eq_params.c, 'c');

    code_status = solve_quad_eq(&quad_eq_params);
    if (code_status != OK)
        return code_status;
    code_status = print_roots(&quad_eq_params);

    return code_status;
#endif
}


ProgramStatus run_all_tests()
{
    ProgramStatus test_status = OK;

    struct QuadEqParameters test_params[]
    {
        {0, 0, 0, 0, 0, INFINITE_NUM_OF_ROOTS},
        {0, 0, 1, 0, 0, NO_ROOTS},
        {0, 1, 0, 0, 0, ONE_ROOT},
        {0, 2.32, -135.952, 58.6, 0, ONE_ROOT},
        {1, 1, 1, 0, 0, NO_ROOTS},
        {1, 4, 4, -2, 0, ONE_ROOT},
        {1, -1, 0.25, 0.5, 0, ONE_ROOT},
        {1, 2, -3, -3, 1, TWO_ROOTS},
        {7.4, 2.1, -5.67, -1.0286554, 0.7448716, TWO_ROOTS},
    };

    for (int i = 0; i < 9; i++)
        test_status = run_test(i+1, &test_params[i]);
    return test_status;
}


ProgramStatus print_infinite_error(const char var[])
{
    printf("error:\n"
          "value of variable %s is infinite", var);
    return NUMBER_IS_INFINITE_ERROR;
}


ProgramStatus print_test_result(int test_number, struct QuadEqParameters* params, struct QuadEqParameters* expected_roots)
{
    if (params->roots_number != expected_roots->roots_number ||
        !is_equal(params->x1, expected_roots->x1) ||
        !is_equal(params->x2, expected_roots->x2))
    {
        printf("Test #%d is failed:\n"
                "a = %lg, b = %lg, c = %lg, x1 = %.7lg, x2 = %.7lg, roots_number = %d\n"
                "Expected: x1 = %.7lg, x2 = %.7lg, roots_number = %d\n\n",
                test_number,
                params->a, params->b, params->c, params->x1, params->x2, params->roots_number,
                expected_roots->x1, expected_roots->x2, expected_roots->roots_number);
        return TEST_FAILED_ERROR;
    }
    else
    {
        printf("Test#%d is succeed\n", test_number);
        return OK;
    }
}


void clear_buffer()
{
    while (getchar() != '\n') {}
}


void input_coeff(double* var_adress, char var_char)
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


bool is_equal(double x, double y)
{
    return abs(x-y) <= 1E-7;
}


ProgramStatus isfinite_check(double x)
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


ProgramStatus print_roots(struct QuadEqParameters* roots)
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
            return OK;
        }
        case ONE_ROOT:
        {
            printf("This equation has only one real root: %.2lg\n", roots->x1);
            return OK;
        }
        case TWO_ROOTS:
        {
            printf("This equation has only two real roots: %.2lg; %.2lg\n", roots->x1, roots->x2);
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
                   "In function print_roots(): variable number = %d is invalid\n", roots->roots_number);
            return PRINT_ROOTS_ERROR_CODE;
        }
    }
}


ProgramStatus solve_line_eq(struct QuadEqParameters* params)
{
    assert(params != NULL);

    ProgramStatus code_status = OK;
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


ProgramStatus solve_quad_eq(struct QuadEqParameters* params)
{
    assert(params != NULL);

    ProgramStatus code_status = OK;
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


ProgramStatus run_test(int test_number, struct QuadEqParameters* expected_roots)
{
    struct QuadEqParameters params = {expected_roots->a, expected_roots->b, expected_roots->c, 0, 0, NO_ROOTS};
    ProgramStatus test_status = OK;
    ProgramStatus code_status = solve_quad_eq(&params);
    if (code_status != OK)
        return code_status;

    test_status = print_test_result(test_number, &params, expected_roots);
    return test_status;
}
