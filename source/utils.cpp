#include <math.h>
#include <string.h>
#include "io.h"
#include "quad.h"
#include "utils.h"


void clear_buffer()
{
    while (getchar() != '\n') {}
}


CodeStatus file_open(const char file_name[], FILE** file_pointer)
{
    *file_pointer = fopen(file_name, "r");
    if (*file_pointer == NULL)
        return FILE_NOT_OPENED_ERROR;
    else
        return OK;
}


CodeStatus isfinite_check(double x)
{
    if (isfinite(x))
        return OK;
    else
        return NUMBER_IS_INFINITE_ERROR;
}


bool is_equal(double x, double y)
{
    return abs(x-y) <= 1E-7;
}


bool is_zero(double x)
{
    return abs(x) <= 1E-7;
}


void swap(void* x, void* y, size_t elem_size)
{
    char temp = ' ';
    for (int i = 0; (size_t) i < elem_size; i++)
    {
        temp = *((char*) x);
        *((char*) x) = *((char*) y);
        *((char*) y) = temp;
        x = ((char*) x) + 1; y = ((char*) y) + 1;
    }
}
