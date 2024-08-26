/*!
    \file
    File with errors and errors output
*/

#include "errors.h"
#include "input_output.h"


void print_code_status(CodeError status)
{
    switch (status)
    {
        case NO_ERROR:
        {
            PRINTGREEN("\n### Program was completed without errors ###\n");
            break;
        }
        case NUMBER_IS_INFINITE_ERROR:
        {
            PRINTRED("\n### Program wasn't completed because of error ###\n### error: NUMBER_IS_INFINITE_ERROR ###\n");
            break;
        }
        case FILE_NOT_OPENED_ERROR:
        {
            PRINTRED("\n### Program wasn't completed because of error ###\n### error: FILE_NOT_OPENED_ERROR ###\n");
            break;
        }
        case PROGRAM_NOT_STARTED:
        {
            PRINTYELLOW("\n### Program wasn't started ###\n");
            break;
        }
        default:
        {
            PRINTRED("\n### Program wasn't completed because of unknown error ###\n");
            break;
        }
    }
}
