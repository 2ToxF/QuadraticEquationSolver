/*!
    \file
    File with input and output functions and macros for color print
*/

#include <stdio.h>
#include <string.h>
#include "input_output.h"
#include "quad.h"
#include "utils.h"

const int MAX_INPUT_LEN = 25;
const char EXIT_STRING[] = "exit";

/*!
    Reads one exact coefficient from stream
    \param[out]  var_adress  Adress to variable where coefficient from stream should be put
    \param[in]   var_char    Char of specific coefficient ('a' or 'b' or 'c')
    \return Status of input (exit program or continue program)
*/
static InputStatus input_coeff(double* var_adress, char var_char);


InputStatus input_all_coeffs(struct QuadEqParameters* input_params)
{
    ASSERT(input_params != NULL);

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
    ASSERT(var_adress != NULL);

    PRINTBLUE("# %c = ", var_char);

    int successfully_input_numbers = 0;

    while ((successfully_input_numbers = scanf("%lf", var_adress)) != 1 || getchar() != '\n')
    {
        if (successfully_input_numbers == 0)
        {
            char input_string[MAX_INPUT_LEN] = {};
            scanf("%s", input_string);
            if (strcmp(input_string, EXIT_STRING) == 0)
                return EXIT;
        }
        clear_buffer();

        PRINTRED("Invalid value, try again\n");
        PRINTBLUE("# %c = ", var_char);
    }

    return CONTINUE;
}


void print_help()
{
    PRINTBLUE("\nUsage:\n"
              "\n"
              "1) .\\QuadSolver.exe [option]\n"
              "Options:\n"
              "    --tests                      Run tests for quadratic_equation_solver\n"
              "    --solve                      Run quadratic_equation_solver\n"
              "    --help                       Print hint with available commands\n"
              "\n"
              "2) make run[option]\n"
              "Options:\n"
              "    _tests                       Run tests for quadratic_equation_solver\n"
              "    _solve                       Run quadratic_equation_solver\n"
              "    _help                        Print hint with available commands\n"
              "         />    >\n"
              "         |  _  _|\n"
              "       _/`= _x =|\n"
              "      /        |\n"
              "   __|   \\    /\n"
              " /  _|    | | |\n"
              " | (  \\___\\_)_)\n"
              " \\__)\n");
}


void print_roots(struct QuadEqParameters* roots)
{
    ASSERT(roots != NULL);

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
                       const struct QuadEqParameters* expected_roots, const struct QuadEqParameters* params)
{
    ASSERT(expected_roots != NULL);
    ASSERT(expected_roots != NULL);
    ASSERT(expected_roots != params);

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
