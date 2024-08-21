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

void input_coeff(double* var_adress, char var_char);
void clear_buffer();
RootsNumber solve_quad_eq(struct QuadEqParameters* params);
RootsNumber solve_line_eq(struct QuadEqParameters* params);
ProgramStatus print_roots(struct QuadEqParameters* roots);
bool is_zero(double x);
bool is_equal(double x, double y);
ProgramStatus test_prog();

int main()
{
#ifdef TEST
    ProgramStatus code_status = OK;
    code_status = test_prog();
    return code_status;
#else
    struct QuadEqParameters quad_eq_params = {};
    ProgramStatus code_status = OK;

    printf("# Enter the coefficients of quadratic equation:\n");
    input_coeff(&quad_eq_params.a, 'a');
    input_coeff(&quad_eq_params.b, 'b');
    input_coeff(&quad_eq_params.c, 'c');

    quad_eq_params.roots_number = solve_quad_eq(&quad_eq_params);
    code_status = print_roots(&quad_eq_params);

    return code_status;
#endif
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


void clear_buffer()
{
    while (getchar() != '\n') {}
}


RootsNumber solve_quad_eq(struct QuadEqParameters* params)
{
    assert(isfinite(params->a));
    assert(isfinite(params->b));
    assert(isfinite(params->c));
    assert(params != NULL);

    double a = params->a, b = params->b, c = params->c;

    double discr = b*b - 4*a*c;
    if (is_zero(a))
        return solve_line_eq(params);
    else if (discr < 0)
        return NO_ROOTS;
    else if (is_zero(discr))
    {
        params->x1 = -b/(2*a);
        return ONE_ROOT;
    }
    else
    {
        params->x1 = (-b - sqrt(discr))/(2*a);
        params->x2 = (-b + sqrt(discr))/(2*a);
        return TWO_ROOTS;
    }
}


RootsNumber solve_line_eq(struct QuadEqParameters* params)
{
    assert(isfinite(params->b));
    assert(isfinite(params->c));
    assert(params != NULL);

    double b = params->b, c = params->c;

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
                   "In function print_roots(): variable number = %d is invalid\n", roots->roots_number);
            return PRINT_ROOTS_ERROR_CODE;
        }
    }
}


bool is_zero(double x)
{
    assert(isfinite(x));
    return abs(x) <= 1E-7;
}


bool is_equal(double x, double y)
{
    assert(isfinite(x));
    assert(isfinite(y));
    return abs(x-y) <= 1E-7;
}


ProgramStatus test_prog()
{
    const double INCORRECT_ROOT = 1000000;
    const double UNCHANGABLE_ROOT = -1000000;
    ProgramStatus test_program_status = OK;
    struct QuadEqParameters test_params[9][2]
    {
        {{0, 0, 0, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}, {0, 0, 0, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, INFINITE_NUM_OF_ROOTS}},
        {{0, 0, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, ONE_ROOT}, {0, 0, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}},
        {{0, 1, 0, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}, {0, 1, 0, 0, UNCHANGABLE_ROOT, ONE_ROOT}},
        {{0, 2.32, -135.952, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}, {0, 2.32, -135.952, 58.6, UNCHANGABLE_ROOT, ONE_ROOT}},
        {{1, 1, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, ONE_ROOT}, {1, 1, 1, UNCHANGABLE_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}},
        {{1, 4, 4, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}, {1, 4, 4, -2, UNCHANGABLE_ROOT, ONE_ROOT}},
        {{1, -1, 0.25, INCORRECT_ROOT, UNCHANGABLE_ROOT, NO_ROOTS}, {1, -1, 0.25, 0.5, UNCHANGABLE_ROOT, ONE_ROOT}},
        {{1, 2, -3, INCORRECT_ROOT, INCORRECT_ROOT, NO_ROOTS}, {1, 2, -3, -3, 1, TWO_ROOTS}},
        {{7.4, 2.1, -5.67, INCORRECT_ROOT, INCORRECT_ROOT, NO_ROOTS}, {7.4, 2.1, -5.67, -1.0286554, 0.7448716, TWO_ROOTS}},
    };

    for (int i = 0; i < 9; i++)
    {
        struct QuadEqParameters changable_params = test_params[i][0];
        struct QuadEqParameters expected_final_params = test_params[i][1];

        changable_params.roots_number = solve_quad_eq(&changable_params);

        if (!is_equal(changable_params.a, expected_final_params.a))
        {
            printf("Test #%d is failed:\n"
                   "The coefficient \"a\" of qudratic equation has been changed\n"
                   "Initial a = %.3lf, final a = %.3lf, expected final a = %.3lf\n\n",
                   i+1, test_params[i][0].a, changable_params.a, expected_final_params.a);
            test_program_status = TEST_FAILED_ERROR;
        }
        if (!is_equal(changable_params.b, expected_final_params.b))
        {
            printf("Test #%d is failed:\n"
                   "The coefficient \"b\" of qudratic equation has been changed\n"
                   "Initial b = %.3lf, final b = %.3lf, expected final b = %.3lf\n\n",
                   i+1, test_params[i][0].b, changable_params.b, expected_final_params.b);
            test_program_status = TEST_FAILED_ERROR;
        }
        if (!is_equal(changable_params.c, expected_final_params.c))
        {
            printf("Test #%d is failed:\n"
                   "The coefficient \"c\" of qudratic equation has been changed\n"
                   "Initial c = %.3lf, final c = %.3lf, expected final c = %.3lf\n\n",
                   i+1, test_params[i][0].c, changable_params.c, expected_final_params.c);
            test_program_status = TEST_FAILED_ERROR;
        }
        if (test_program_status == TEST_FAILED_ERROR)
            return test_program_status;

        if (!is_equal(changable_params.x1, expected_final_params.x1))
        {
            printf("Test #%d is failed:\n"
                   "The root \"x1\" of qudratic equation is incorrect\n"
                   "Initial x1 = %.7lf, final x1 = %.7lf, expected final x1 = %.7lf\n"
                   "Coefficient of the equation: a = %.3lf, b = %.3lf, c = %.3lf\n\n",
                   i+1, test_params[i][0].x1, changable_params.x1, expected_final_params.x1,
                   expected_final_params.a, expected_final_params.b, expected_final_params.c);
            test_program_status = TEST_FAILED_ERROR;
        }
        if (!is_equal(changable_params.x2, expected_final_params.x2))
        {
            printf("Test #%d is failed:\n"
                   "The root \"x2\" of qudratic equation is incorrect\n"
                   "Initial x2 = %.7lf, final x2 = %.7lf, expected final x2 = %.7lf\n"
                   "Coefficient of the equation: a = %.3lf, b = %.3lf, c = %.3lf\n\n",
                   i+1, test_params[i][0].x2, changable_params.x2, expected_final_params.x2,
                   expected_final_params.a, expected_final_params.b, expected_final_params.c);
            test_program_status = TEST_FAILED_ERROR;
        }
        if (changable_params.roots_number != expected_final_params.roots_number)
        {
            printf("Test #%d is failed:\n"
                   "The number of roots \"roots_number\" of qudratic equation is incorrect\n"
                   "Initial roots_number = %d, final roots_number = %d, expected final roots_number = %d\n"
                   "Coefficient of the equation: a = %.3lf, b = %.3lf, c = %.3lf\n\n",
                   i+1, test_params[i][0].roots_number, changable_params.roots_number, expected_final_params.roots_number,
                   expected_final_params.a, expected_final_params.b, expected_final_params.c);
            test_program_status = TEST_FAILED_ERROR;
        }
    }

    return test_program_status;
}
