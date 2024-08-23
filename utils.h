#ifndef UTILS_H
#define UTILS_H

#include "io.h"
#include "quad.h"

#define ASSERT(assertion) if (!assertion) \
                          { \
                              PRINTRED("\033[0;31m Assertion failed:\n" \
                                       "file %s:    func %s:    line %d:\n", \
                                       __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                                       exit(EXIT_FAILURE); \
                          }

void file_open(const char file_name[], FILE** file_pointer);
CodeStatus isfinite_check(double x);
bool is_equal(double x, double y);
bool is_zero(double x);
void swap(void* x, void* y, size_t elem_size);

#endif
