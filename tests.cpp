#include <stdio.h>
#include <math.h>
#include "quad.h"
#include "tests.h"

enum TestStatus
{
    TEST_SUCCEED,
    TEST_FAILED,
};

static bool is_equal(double x, double y);
static void print_test_result(TestStatus tes_status, int test_number,
                              const struct QuadEqParameters* params, struct QuadEqParameters* expected_roots);
static CodeStatus run_test(TestStatus* test_status, const struct QuadEqParameters* expected_roots,
                           struct QuadEqParameters* params);


static bool is_equal(double x, double y)
{
    return abs(x-y) <= 1E-7;
}

static void print_test_result(TestStatus test_status, int test_number,
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
