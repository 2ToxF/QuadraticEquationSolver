/*!
    \file
    File with code for testing main program
*/

#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include "quad.h"

/// Result of the current test
enum TestStatus
{
    TEST_SUCCEED,  ///< Test successfully passed
    TEST_FAILED,   ///< Test failed
};

/*!
    Run the sequence of test
    \return Status of completing the program
*/
CodeStatus run_all_tests();

/*!
    Starts the test program
    \return Status of completing the program
*/
CodeStatus run_main_test();

#endif
