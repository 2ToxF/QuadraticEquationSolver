#include <math.h>
#include <stdio.h>
#include "io.h"
#include "quad.h"
#include "tests.h"

static bool is_equal(double x, double y);
static CodeStatus run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                           struct QuadEqParameters* params);


static bool is_equal(double x, double y)
{
    return abs(x-y) <= 1E-7;
}


CodeStatus run_all_tests()
{
    CodeStatus code_status = OK;
    TestStatus test_status = TEST_SUCCEED;

    const char tests_file_name[] = "tests.txt";
    FILE* tests_file = fopen(tests_file_name, "r");
    if (tests_file == NULL)
    {
        PRINTRED("error:\n"
                 "run_all_tests(): FILE_NOT_OPENED_ERROR");
        return FILE_NOT_OPENED_ERROR;
    }

    int succeed_test_count = 0;
    int test_count = 0;
    struct QuadEqParameters expected_params = {};
    int temp_roots_number = 0;

    while (fscanf(tests_file, " %lf | %lf | %lf | %lf | %lf | %d \n",
                  &expected_params.a, &expected_params.b, &expected_params.c,
                  &expected_params.x1, &expected_params.x2,
                  &temp_roots_number) != EOF)
    {
        expected_params.roots_number = (RootsNumber) temp_roots_number;
        struct QuadEqParameters current_test = {expected_params.a, expected_params.b, expected_params.c, 0, 0, NO_ROOTS};

        code_status = run_test(&test_status, &expected_params, &current_test);
        if (code_status != OK)
            return code_status;

        if (test_status == TEST_SUCCEED)
            succeed_test_count++;
        test_count++;

        print_test_result(test_status, test_count, &expected_params, &current_test);
    }

    PRINTGREEN("PASSED: %d/%d", succeed_test_count, test_count);
    return code_status;
}


CodeStatus run_main_test()
{
    CodeStatus code_status = OK;
    code_status = run_all_tests();
    return code_status;
}


static CodeStatus run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
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
