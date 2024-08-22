#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "io.h"

const int MAX_INPUT_LEN = 25;
const char EXIT_STRING[] = "exit";

static void clear_buffer();
static InputStatus input_coeff(double* var_adress, char var_char);


static void clear_buffer()
{
    while (getchar() != '\n') {}
}


InputStatus input_all_coeffs(struct QuadEqParameters* input_params)
{
    if (input_coeff(&input_params->a, 'a') == EXIT)
        return EXIT;
    if (input_coeff(&input_params->b, 'b') == EXIT)
        return EXIT;
    if (input_coeff(&input_params->c, 'c') == EXIT)
        return EXIT;
    return CONTINUE;
}


static InputStatus input_coeff(double* var_adress, char var_char)
{
    assert(var_adress != NULL);

    printf("# %c = ", var_char);

    while (scanf("%lf", var_adress) != 1)
    {
        char input_string[MAX_INPUT_LEN] = {};
        scanf("%s", input_string);
        if (strcmp(input_string, EXIT_STRING) == 0)
            return EXIT;
        clear_buffer();

        printf("Invalid value, try again\n");
        printf("# %c = ", var_char);
    }

    clear_buffer();

    return CONTINUE;
}


void print_code_status(CodeStatus status)
{
    switch (status)
    {
        case OK:
        {
            printf("\nProgram was done without errors\n");
            break;
        }
        case NUMBER_IS_INFINITE_ERROR:
        {
            printf("\nProgram wasn't done because of error\nerror: NUMBER_IS_INFINITE_ERROR\n");
            break;
        }
        case PROGRAM_NOT_STARTED:
        {
            printf("Program wasn't started");
            break;
        }

        default:
        {
            printf("\nProgram wasn't done because of unknown error\n");
            break;
        }
    }
}


void print_help()
{
    printf("\nUsage: ./qe_solver.exe [option]  ||  make run\n"
            "Options:\n"
            "    --tests                      Run tests for quadratic_equation_solver\n"
            "    --solve                      Run quadratic_equation_solver\n");
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
