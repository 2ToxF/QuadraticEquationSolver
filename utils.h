#ifndef UTILS_H
#define UTILS_H

#include "io.h"
#include "quad.h"

/// Assert with red printing and showing the place where the issue was found
#define ASSERT(assertion) if (!assertion) \
                          { \
                              PRINTRED("\033[0;31m Assertion failed:\n" \
                                       "file %s:    func %s:    line %d:\n", \
                                       __FILE__, __PRETTY_FUNCTION__, __LINE__); \
                                       exit(EXIT_FAILURE); \
                          }
/// Assert with red printing and showing the place where the issue was found

/*!
    Clear buffer with input chars
*/
void clear_buffer();

/*!
    Open file and check wheter the file_pointer is NULL
    \param[in]   file_name     The name of file which need to be opened
    \param[out]  file_pointer  The pointer of opened file
*/
void file_open(const char file_name[], FILE** file_pointer);

/*!
    Check wheter the variable has infinite value
    \param  x  The variable that should be checked
    \return Status of completing the program
*/
CodeStatus isfinite_check(double x);

/*!
    Check wheter two float number are equal
    \param[in]  x, y  The numbers that should be checked
    \return The result check
*/
bool is_equal(double x, double y);

/*!
    Check wheter the float number is equal to zero
    \param[in]  x  The number that should be checked
    \return The result check
*/
bool is_zero(double x);

/*!
    Swap the values of two variables
    \param[in, out]  x, y  The variables which values should be changed
*/
void swap(void* x, void* y, size_t elem_size);

#endif
