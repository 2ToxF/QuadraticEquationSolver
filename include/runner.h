/*!
    \file
    File with the main program runner function
*/

#ifndef RUNNER_H
#define RUNNER_H

#include "cmd_processing.h"
#include "errors.h"

/*!
    Starts the program depending on chosen option
    \param[in]  option  Type of command entered in command line
    \return Status of completing the program
*/
CodeError run_program(CmdOption option);

#endif
