#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include "quad.h"

enum TestStatus
{
    TEST_SUCCEED,
    TEST_FAILED,
};

CodeStatus run_all_tests();
CodeStatus run_main_test();

#endif
