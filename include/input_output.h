/*!
    \file
    File with input and output functions and macros for color print
*/

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include "quad.h"
#include "tests.h"

/// Macros for red color print
#define PRINTRED(text, ...)    printf("\033[0;31m" text "\033[0;37m", ## __VA_ARGS__)
/// Macros for green color print
#define PRINTGREEN(text, ...)  printf("\033[0;32m" text "\033[0;37m", ## __VA_ARGS__)
/// Macros for yellow color print
#define PRINTYELLOW(text, ...) printf("\033[0;33m" text "\033[0;37m", ## __VA_ARGS__)
/// Macros for blue color print
#define PRINTBLUE(text, ...)   printf("\033[0;34m" text "\033[0;37m", ## __VA_ARGS__)
/// Macros for purple color print
#define PRINTPURPLE(text, ...) printf("\033[0;35m" text "\033[0;37m", ## __VA_ARGS__)
/// Macros for cyan color print
#define PRINTCYAN(text, ...)   printf("\033[0;36m" text "\033[0;37m", ## __VA_ARGS__)

/// Status of input (exit program or continue program)
enum InputStatus
{
    EXIT,      ///< Program should be stopped immediately
    CONTINUE,  ///< Program should be continued
};

/*!
    Starts program of reading coefficients of the equation from stream
    \param[in]  input_params  Struct in which the coefficients of the equation will be entered
    \return Status of input (exit program or continue program)
*/
InputStatus input_all_coeffs(struct QuadEqParameters* input_params);

/*!
    Prints hint with available options for user
*/
void print_help();

/*!
    Prints roots of equation
    \param[in,out]  roots  Struct with roots of equation
*/
void print_roots(struct QuadEqParameters* roots);

/*!
    Prints test result
    \param[in]  test_status     Status of test (succeed or failed)
    \param[in]  test_number     Test number
    \param[in]  expected_roots  Roots that were expected in the end of test
    \param[in]  params          Parameters of the test (coefficients and roots got from program)
*/
void print_test_result(TestStatus test_status, int test_number,
                       const struct QuadEqParameters* expected_roots, const struct QuadEqParameters* params);

#endif
