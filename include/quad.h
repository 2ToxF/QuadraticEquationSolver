/*!
    \file
    File with code for solving quadratic equation and input coefficients of it
*/

#ifndef QUAD_H
#define QUAD_H

#include "errors.h"

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
CodeError run_main_solve();

/*!
    Solves the specific equation
    \param[in, out]  params  Parameters for equation
    \return Status of completing the program
*/
CodeError solve_quad_eq(struct QuadEqParameters* params);

#endif
