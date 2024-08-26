/*!
    \file
    File with code for testing main program
*/

#include <math.h>
#include "input_output.h"
#include "quad.h"
#include "tests.h"
#include "utils.h"

/// const
const char TESTS_FILE_NAME[] = "tests.txt";

/*!
    Runs exact test with specific parameters
    \param[out]      test_status     Result of the test
    \param[in]       expected_roots  Parameters that should be in the end of the test
    \param[in, out]  params          Parameters send to the equation solver in the beginning of the test
    \return Status of completing the program
*/
static CodeError run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                           struct QuadEqParameters* params);


CodeError run_all_tests()
{
    CodeError code_status = NO_ERROR;
    TestStatus test_status = TEST_SUCCEED;

    FILE* tests_file = NULL;
    if((code_status = file_open(TESTS_FILE_NAME, &tests_file)) != NO_ERROR)
        return code_status;

    int succeed_test_count = 0;
    int test_count = 0;
    struct QuadEqParameters expected_params = {};

    while (fscanf(tests_file, " %lf | %lf | %lf | %lf | %lf | %d \n",
                  &expected_params.a, &expected_params.b, &expected_params.c,
                  &expected_params.x1, &expected_params.x2,
                  (int*) &expected_params.roots_number) != EOF)
    {
        struct QuadEqParameters current_test = {expected_params.a, expected_params.b, expected_params.c, 0, 0, NO_ROOTS};

        if ((code_status = run_test(&test_status, &expected_params, &current_test)) != NO_ERROR)
            return code_status;

        if (test_status == TEST_SUCCEED)
            succeed_test_count++;
        test_count++;

        print_test_result(test_status, test_count, &expected_params, &current_test);
    }

    PRINTGREEN("PASSED: %d/%d\n", succeed_test_count, test_count);
    return code_status;
}


CodeError run_main_test()
{
    CodeError code_status = NO_ERROR;
    code_status = run_all_tests();
    return code_status;
}


static CodeError run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                           struct QuadEqParameters* params)
{
    ASSERT(expected_roots != NULL);
    ASSERT(params != NULL);
    ASSERT(expected_roots != params);

    CodeError code_status = solve_quad_eq(params);
    if (code_status != NO_ERROR)
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
