/**
 * @file start_lib.h
 * @author Maciej Fender
 * @brief starting module
 * @version 0.1
 * @date 2021-03-20
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
#include <syslog.h>


int daemon2();

void logg(char* message);

char* get_output_file_name();

char* get_input_file_name();

int parse_arguments(int argc, char **argv);

#endif // START_LIB_INCLUDED