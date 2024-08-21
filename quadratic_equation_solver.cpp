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
enum CodeStatus
{
    OK,
    NUMBER_IS_INFINITE_ERROR=1,
};
enum TestStatus
{
    TEST_SUCCEED,
    TEST_FAILED,
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

void clear_buffer();
void input_coeff(double* var_adress, char var_char);
bool is_equal(double x, double y);
CodeStatus isfinite_check(double x);
bool is_zero(double x);
CodeStatus print_infinite_error(const char var[]);
void print_roots(struct QuadEqParameters* roots);
void print_test_result(TestStatus tes_status, int test_number,
                       const struct QuadEqParameters* params, struct QuadEqParameters* expected_roots);
CodeStatus run_all_tests();
CodeStatus run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                    struct QuadEqParameters* params);
CodeStatus solve_line_eq(struct QuadEqParameters* params);
CodeStatus solve_quad_eq(struct QuadEqParameters* params);

int main()
{
#ifdef TEST
    CodeStatus code_status = OK;
    code_status = run_all_tests();
    return code_status;
#else
    struct QuadEqParameters quad_eq_params = {};
    CodeStatus code_status = OK;

    printf("# Enter the coefficients of quadratic equation:\n");
    input_coeff(&quad_eq_params.a, 'a');
    input_coeff(&quad_eq_params.b, 'b');
    input_coeff(&quad_eq_params.c, 'c');

    code_status = solve_quad_eq(&quad_eq_params);
    if (code_status != OK)
        return code_status;
    print_roots(&quad_eq_params);
    return code_status;
#endif
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


CodeStatus isfinite_check(double x)
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


CodeStatus print_infinite_error(const char var[])
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


void print_test_result(TestStatus test_status, int test_number,
                       const struct QuadEqParameters* params, struct QuadEqParameters* expected_roots)
{
    if (test_status == TEST_FAILED)
    {
        printf("Test #%d is failed:\n"
                "a = %lg, b = %lg, c = %lg, x1 = %.7lg, x2 = %.7lg, roots_number = %d\n"
                "Expected: x1 = %.7lg, x2 = %.7lg, roots_number = %d\n\n",
                test_number,
                params->a, params->b, params->c, params->x1, params->x2, params->roots_number,
                expected_roots->x1, expected_roots->x2, expected_roots->roots_number);
    }
    else
    {
        printf("Test#%d is succeed\n", test_number);
    }
}


CodeStatus run_all_tests()
{
    CodeStatus code_status = OK;
    TestStatus test_status = TEST_SUCCEED;

    const struct QuadEqParameters test_params[]
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
    {
        struct QuadEqParameters current_test = {test_params[i].a, test_params[i].b, test_params[i].c, 0, 0, NO_ROOTS};
        code_status = run_test(&test_status, &test_params[i], &current_test);
        if (code_status != OK)
            return code_status;
        print_test_result(test_status, i+1, &test_params[i], &current_test);
    }

    return code_status;
}


CodeStatus run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                    struct QuadEqParameters* params)
{
    CodeStatus code_status = solve_quad_eq(params);
    if (code_status != OK)
        return code_status;

    if (params->roots_number != expected_roots->roots_number ||
        !is_equal(params->x1, expected_roots->x1) ||
        !is_equal(params->x2, expected_roots->x2))
    {
        *test_status = TEST_FAILED;
    }
    else
        *test_status = TEST_SUCCEED;
    return code_status;
}


CodeStatus solve_line_eq(struct QuadEqParameters* params)
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
