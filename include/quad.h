/*!
    \file
    File with code for solving quadratic equation and input coefficients of it
*/

#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>

/// Status of completing the program
enum CodeStatus
{
    OK,                        ///< Program was done without errors
    NUMBER_IS_INFINITE_ERROR,  ///< The variable in program got infinite value
    FILE_NOT_OPENED_ERROR,     ///< File was not opened or found
    PROGRAM_NOT_STARTED,       ///< Program wasn't started due to error in command line options
};

/// Status of input (exit program or continue program)
enum InputStatus
{
    EXIT,      ///< Program should be stopped immediately
    CONTINUE,  ///< Program should be continued
};

/// Number of equation's roots
enum RootsNumber
{
    NO_ROOTS,               ///< Equation has no roots
    ONE_ROOT,               ///< Equation has only one root
    TWO_ROOTS,              ///< Equation has only two roots
    INFINITE_NUM_OF_ROOTS,  ///< Equation has infinte number of roots
};

/// Parameters for equation
struct QuadEqParameters
{
    double a;                  ///< Coefficient a
    double b;                  ///< Coefficient b
    double c;                  ///< Coefficient c
    double x1;                 ///< Less root
    double x2;                 ///< Greater root
    RootsNumber roots_number;  ///< Number of roots
};

/*!
    Starts input coefficients and colving the equation
    \return Status of completing the program
*/
CodeStatus run_main_solve();

/*!
    Solve the quadratic equation
    \param[in, out]  params  Parameters for equation
    \return Status of completing the program
*/
CodeStatus solve_quad_eq(struct QuadEqParameters* params);

#endif
