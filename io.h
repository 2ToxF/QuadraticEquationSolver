#ifndef IO_H
#define IO_H

#include "cmd_processing.h"
#include "tests.h"

InputStatus input_all_coeffs(struct QuadEqParameters* input_params);
void print_code_status(CodeStatus status);
void print_help();
CodeStatus print_infinite_error(const char var[]);
void print_roots(struct QuadEqParameters* roots);
void print_test_result(TestStatus tes_status, int test_number,
                       const struct QuadEqParameters* params, struct QuadEqParameters* expected_roots);

#endif
