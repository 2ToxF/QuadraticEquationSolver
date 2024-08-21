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
struct QuadEqRoots
{
    double x1;
    double x2;
    RootsNumber roots_number;
};

ProgramStatus call_tests();
void clear_buffer();
ProgramStatus print_infinite_error(const char var[]);
void input_coeff(double* var_adress, char var_char);
bool is_equal(double x, double y);
ProgramStatus isfinite_check(double x);
bool is_zero(double x);
ProgramStatus print_roots(struct QuadEqParameters* roots);
ProgramStatus solve_line_eq(struct QuadEqParameters* params);
ProgramStatus solve_quad_eq(struct QuadEqParameters* params);
ProgramStatus test(int test_number, struct QuadEqParameters params, struct QuadEqRoots expected_roots);

int main()
{
#ifdef TEST
    ProgramStatus code_status = OK;
    code_status = call_tests();
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


ProgramStatus call_tests()
{
    const double INCORRECT_ROOT = 1000000;
    const double UNCHANGABLE_ROOT = -1000000;
    ProgramStatus test_status = OK;

    struct QuadEqParameters test_params[]
    {
        {0, 0, 0, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {0, 0, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, ONE_ROOT},
        {0, 1, 0, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {0, 2.32, -135.952, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {1, 1, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, ONE_ROOT},
        {1, 4, 4, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {1, -1, 0.25, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {1, 2, -3, INCORRECT_ROOT, INCORRECT_ROOT, NO_ROOTS},
        {7.4, 2.1, -5.67, INCORRECT_ROOT, INCORRECT_ROOT, NO_ROOTS},
    };
    struct QuadEqRoots expected_roots[]
    {
        {UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, INFINITE_NUM_OF_ROOTS},
        {UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {0, UNCHANGABLE_ROOT, ONE_ROOT},
        {58.6, UNCHANGABLE_ROOT, ONE_ROOT},
        {UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS},
        {-2, UNCHANGABLE_ROOT, ONE_ROOT},
        {0.5, UNCHANGABLE_ROOT, ONE_ROOT},
        {-3, 1, TWO_ROOTS},
        {-1.0286554, 0.7448716, TWO_ROOTS},
    };

    for (int i = 0; i < 9; i++)
        test_status = test(i+1, test_params[i], expected_roots[i]);
    return test_status;
}


ProgramStatus print_infinite_error(const char var[])
{
    printf("error:\n"
          "value of variable %s is infinite", var);
    return NUMBER_IS_INFINITE_ERROR;
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


ProgramStatus test(int test_number, struct QuadEqParameters params, struct QuadEqRoots expected_roots)
{
    ProgramStatus test_status = OK;
    ProgramStatus code_status = solve_quad_eq(&params);
    if (code_status != OK)
        return code_status;

    if (params.roots_number != expected_roots.roots_number ||
        !is_equal(params.x1, expected_roots.x1) ||
        !is_equal(params.x2, expected_roots.x2))
    {
        printf("Test #%d is failed:\n"
                "a = %lg, b = %lg, c = %lg, x1 = %.7lg, x2 = %.7lg, roots_number = %d\n"
                "Expected: x1 = %.7lg, x2 = %.7lg, roots_number = %d\n\n",
                test_number,
                params.a, params.b, params.c, params.x1, params.x2, params.roots_number,
                expected_roots.x1, expected_roots.x2, expected_roots.roots_number);
        test_status = TEST_FAILED_ERROR;
    }

    return test_status;
}
