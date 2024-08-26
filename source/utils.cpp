/*!
    \file
    File with utilities
*/

#include <math.h>
#include <string.h>
#include "quad.h"
#include "utils.h"

const double PRECISION_LIMIT = 1E-7;


void clear_buffer()
{
    int char_from_buffer = 0;
    while ((char_from_buffer = getchar()) != '\n' && char_from_buffer != EOF) {}
}


CodeError file_open(const char file_name[], FILE** file_pointer)
{
    *file_pointer = fopen(file_name, "r");

    if (*file_pointer == NULL)
        return FILE_NOT_OPENED_ERROR;
    else
        return NO_ERROR;
}


CodeError isfinite_check(double x)
{
    if (isfinite(x))
        return NO_ERROR;
    else
        return NUMBER_IS_INFINITE_ERROR;
}


bool is_equal(double x, double y)
{
    return is_zero(x-y);        // magic const
}


bool is_zero(double x)
{
    return fabs(x) <= PRECISION_LIMIT;          // xueviu number
}


void swap(void* x, void* y, size_t elem_size)
{
    ASSERT(x != NULL);
    ASSERT(y != NULL);
    ASSERT(x != y);

    char temp = 0;
    for (size_t i = 0; i < elem_size; i++)
    {
        temp = *((char*) x);
        *((char*) x) = *((char*) y);
        *((char*) y) = temp;
        x = ((char*) x) + 1; y = ((char*) y) + 1;
    }
}
