#ifndef UTILS_H
#define UTILS_H

#include "quad.h"

CodeStatus assert_isfinite(double x, const char* file, const char* func, int line);
CodeStatus file_open(const char file_name[], FILE** file_pointer,
                     const char* file, const char* func, int line);
bool is_equal(double x, double y);
bool is_zero(double x);

#endif
