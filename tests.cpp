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

    const struct QuadEqParameters test_params[]
    {
    //-------------------------------------------------------------
    //   a    b        c       x1         x2         roots_number
    //-------------------------------------------------------------
        {0,   0,       0,      0,         0,         INFINITE_NUM_OF_ROOTS},
        {0,   0,       1,      0,         0,         NO_ROOTS},
        {0,   1,       0,      0,         0,         ONE_ROOT},
        {0,   2.32, -135.952, 58.6,       0,         ONE_ROOT},
        {1,   1,       1,      0,         0,         NO_ROOTS},
        {1,   4,       4,     -2,         0,         ONE_ROOT},
        {1,  -1,       0.25,   0.5,       0,         ONE_ROOT},
        {1,   2,      -3,     -3,         1,         TWO_ROOTS},
        {7.4, 2.1,    -5.67,  -1.0286554, 0.7448716, TWO_ROOTS},
    };

    const int test_count = sizeof (test_params) / sizeof (QuadEqParameters);

    for (int i = 0; i < test_count; i++)
    {
        struct QuadEqParameters current_test = {test_params[i].a, test_params[i].b, test_params[i].c, 0, 0, NO_ROOTS};
        code_status = run_test(&test_status, &test_params[i], &current_test);
        if (code_status != OK)
            return code_status;
        print_test_result(test_status, i+1, &test_params[i], &current_test);
    }

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
