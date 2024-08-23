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

    PRINTBLUE("# %c = ", var_char);

    while (scanf("%lf", var_adress) != 1)
    {
        char input_string[MAX_INPUT_LEN] = {};
        scanf("%s", input_string);
        if (strcmp(input_string, EXIT_STRING) == 0)
            return EXIT;
        clear_buffer();

        PRINTRED("Invalid value, try again\n");
        PRINTBLUE("# %c = ", var_char);
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
            PRINTGREEN("\n### Program was done without errors ###\n");
            break;
        }
        case NUMBER_IS_INFINITE_ERROR:
        {
            PRINTRED("\n### Program wasn't done because of error\nerror: NUMBER_IS_INFINITE_ERROR ###\n");
            break;
        }
        case FILE_NOT_OPENED_ERROR:
        {
            PRINTRED("\n### Program wasn't done because of error\nerror: FILE_NOT_OPENED_ERROR ###\n");
            break;
        }
        case NULL_FILE_INFO:
        {
            PRINTRED("\n### Program wasn't done because of error\nerror: FILE_NOT_OPENED_ERROR ###\n");
            break;
        }
        case PROGRAM_NOT_STARTED:
        {
            PRINTYELLOW("\n### Program wasn't started ###\n");
            break;
        }
        default:
        {
            PRINTRED("\n### Program wasn't done because of unknown error ###\n");
            break;
        }
    }
}


void print_help()
{
    PRINTBLUE("\nUsage: ./qe_solver.exe [option]  ||  make run\n"
            "Options:\n"
            "    --tests                      Run tests for quadratic_equation_solver\n"
            "    --solve                      Run quadratic_equation_solver\n");
}


CodeStatus print_infinite_error(const char var[])
{
    PRINTRED("error:\n"
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
            PRINTPURPLE("This equation has no real roots\n");
            break;
        }
        case ONE_ROOT:
        {
            PRINTPURPLE("This equation has only one real root: %lg\n", roots->x1);
            break;
        }
        case TWO_ROOTS:
        {
            PRINTPURPLE("This equation has only two real roots: %lg; %lg\n", roots->x1, roots->x2);
            break;
        }
        case INFINITE_NUM_OF_ROOTS:
        {
            PRINTPURPLE("This equation has an infinite number of real roots\n");
            break;
        }
        default:
        {
            PRINTRED("print_roots(): default situation");
            break;
        }
    }
}


void print_test_result(TestStatus test_status, int test_number,
                       struct QuadEqParameters* expected_roots, const struct QuadEqParameters* params)
{
    if (test_status == TEST_FAILED)
    {
        PRINTRED("Test #%d is failed:\n"
                 "a = %lg, b = %lg, c = %lg, x1 = %.7lg, x2 = %.7lg, roots_number = %d\n"
                 "Expected: x1 = %.7lg, x2 = %.7lg, roots_number = %d\n\n",
                 test_number,
                 params->a, params->b, params->c, params->x1, params->x2, params->roots_number,
                 expected_roots->x1, expected_roots->x2, expected_roots->roots_number);
    }
    else
    {
        PRINTGREEN("Test #%d is passed\n", test_number);
    }
}
