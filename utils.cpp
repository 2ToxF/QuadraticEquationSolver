#include "io.h"
#include "math.h"
#include "utils.h"


CodeStatus assert_isfinite(double x, const char* file, const char* func, int line)
{
    if (isfinite(x))
        return OK;
    else
    {
        PRINTRED("file %s:    In function %s:    line %d:\n"
                 "file %s:    In function %s:    line %d:\n"
                 "error: value of variable is infinite\n",
                 __FILE__, __FUNCTION__, __LINE__,
                 file, func, line);
        return NUMBER_IS_INFINITE_ERROR;
    }
}


CodeStatus file_open(const char file_name[], FILE** file_pointer,
                     const char* file, const char* func, int line)
{
    *file_pointer = fopen(file_name, "r");
    if (*file_pointer == NULL)
    {
        PRINTRED("file %s:    In function %s:    line %d:\n"
                 "file %s:    In function %s:    line %d:\n"
                 "error: file wasn't found or opened\n",
                 __FILE__, __FUNCTION__, __LINE__,
                 file, func, line);
        return FILE_NOT_OPENED_ERROR;
    }
    return OK;
}


bool is_equal(double x, double y)
{
    return abs(x-y) <= 1E-7;
}


bool is_zero(double x)
{
    return abs(x) <= 1E-7;
}
