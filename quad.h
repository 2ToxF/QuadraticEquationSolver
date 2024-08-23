#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>

enum CodeStatus
{
    OK,
    NUMBER_IS_INFINITE_ERROR,
    FILE_NOT_OPENED_ERROR,
    PROGRAM_NOT_STARTED,
};
enum InputStatus
{
    EXIT,
    CONTINUE,
};
enum RootsNumber
{
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INFINITE_NUM_OF_ROOTS,
};

struct QuadEqParameters
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    RootsNumber roots_number;
};

CodeStatus run_main_solve();
CodeStatus solve_quad_eq(struct QuadEqParameters* params);

#endif
