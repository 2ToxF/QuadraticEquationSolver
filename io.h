#ifndef IO_H
#define IO_H

#include "cmd_processing.h"
#include "tests.h"

#define PRINTRED(text, ...)    printf("\033[0;31m" text "\033[0;37m", ## __VA_ARGS__)
#define PRINTGREEN(text, ...)  printf("\033[0;32m" text "\033[0;37m", ## __VA_ARGS__)
#define PRINTYELLOW(text, ...) printf("\033[0;33m" text "\033[0;37m", ## __VA_ARGS__)
#define PRINTBLUE(text, ...)   printf("\033[0;34m" text "\033[0;37m", ## __VA_ARGS__)
#define PRINTPURPLE(text, ...) printf("\033[0;35m" text "\033[0;37m", ## __VA_ARGS__)
#define PRINTCYAN(text, ...)   printf("\033[0;36m" text "\033[0;37m", ## __VA_ARGS__)

InputStatus input_all_coeffs(struct QuadEqParameters* input_params);
void print_code_status(CodeStatus status);
void print_help();
void print_roots(struct QuadEqParameters* roots);
void print_test_result(TestStatus tes_status, int test_number,
                       struct QuadEqParameters* expected_roots, const struct QuadEqParameters* params);

#endif
