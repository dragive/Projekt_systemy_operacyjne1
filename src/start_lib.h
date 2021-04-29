/**
 * @file start_lib.h
 * @author Maciej Fender
 * @brief start function used on start of the program
 * @version 1
 * @date 2021-03-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef START_LIB_INCLUDED
#define START_LIB_INCLUDED

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/** \brief Function to run program as daemon
 *
 * \return new process id; pid of the created daemon
 * \author MF
 */

int daemon2();

/**
 * @brief Global variable storing name of input file
 */
char* input_file;

/**
 * @brief Global variable storing name of output file
 */
char* output_file;

/**
 * @brief Function gets arguments from start of the program, validate and assigns to propriete  global variable.
 *
 * @param argc Number of arguments
 * @param argv The array of arguments.
 * @return int Indicator whether process of parsing arguments gone well. When it's ok then 0, else something gone wrong.
 * @author MF
 */
int parse_arguments(int argc, char **argv);
/** \brief Getter of input_file
 * \author MF
 */
char* get_input_file_name();
/** \brief Getter of output_file
 * \author MF
 */
char* get_output_file_name();

#endif // START_LIB_INCLUDED



