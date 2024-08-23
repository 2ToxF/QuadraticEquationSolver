#include <mem.h>
#include "io.h"
#include "math.h"
#include "utils.h"


void clear_buffer()
{
    while (getchar() != '\n') {}
}


void file_open(const char file_name[], FILE** file_pointer)
{
    *file_pointer = fopen(file_name, "r");
    ASSERT(*file_pointer != NULL);
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
    void* swap_buffer = malloc(elem_size);
    memcpy(swap_buffer, x, elem_size);
    memcpy(x, y, elem_size);
    memcpy(y, swap_buffer, elem_size);
    free(swap_buffer);
}
