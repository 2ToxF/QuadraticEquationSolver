#ifndef QUAD_H
#define QUAD_H

#include <stdio.h>

enum CodeStatus
{
    OK,
    NUMBER_IS_INFINITE_ERROR=1,
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

InputStatus input_coeff(double* var_adress, char var_char);
void print_roots(struct QuadEqParameters* roots);
CodeStatus solve_quad_eq(struct QuadEqParameters* params);

#endif
