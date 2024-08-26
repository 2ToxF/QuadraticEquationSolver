/*!
    \file
    File with errors and errors output
*/

#ifndef ERRORS_H
#define ERRORS_H

/// Status of completing the program
enum CodeError
{
    NO_ERROR,                  ///< Program was done without errors
    NUMBER_IS_INFINITE_ERROR,  ///< The variable in program got infinite value
    FILE_NOT_OPENED_ERROR,     ///< File was not opened or found
    PROGRAM_NOT_STARTED,       ///< Program wasn't started due to error in command line options
};

/*!
    Prints the result of completeing the program
    \param[in]  status  Status of program completing
*/
void print_code_status(CodeError status);

#endif
