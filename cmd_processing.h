/*!
    \file
    File with code for reading commands from command line when the program starts
*/

#ifndef CMD_PROCESSING_H
#define CMD_PROCESSING_H

/// Type of command entered in command line
enum CmdOption
{
    TEST,     ///< Shows that program will start in test-mode
    SOLVE,    ///< Shows that mrogram will start in classical mode with entering coefficients
    HELP,     ///< Shows that program will print hint
    UNKNOWN,  ///< Shows that program doesn't know entered option/options
};

/*!
    Reads and return type of command from command line when the prigram starts
    \param[in]  options_number  Number of options entered in the command line
    \param[in]  options         List of options entered in the command line
    \return Type of option entered in the command line
*/
CmdOption cmd_read(int options_number, const char* options[]);

#endif
