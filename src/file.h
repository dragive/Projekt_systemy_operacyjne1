/**
 * @file file.h
 * @author Maciej Fender
 * @brief file handeling module
 * @version 0.1
 * @date 2021-03-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef FILE_INCLUDED
#define FILE_INCLUDED


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "singleLine.h"


typedef struct
{
    char * value;    /** Pointer to table of chars read from file */
    int size_max;               /** Max size which can be currently stored */
    int size_current;           /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
}singleLine;
/**
 * @brief Function used to open input file for reading
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @author MF
 */
//int open_to_read_file(const char *  file_name);
/**
 * @brief Function used to open output file for appending
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @see open_to_read_input_file()
 * @author MF
 */
//int open_to_append_file(const char *  file_name);

/** @brief Get the new character from file and if reach end of file than change status.
 *
 * @param file File which character will be read from
 * @return char Character read from file
 * @author KF
 */
char get_new_character_from_file(int file,int* status);

/** @brief Get the new character from file and if reach end of file than change status.
 * @param file File which character will be read from
 * @param status Using to check status of reaching the end of file
 * @return line from file
 * @author KF
 */
singleLine* get_line_from_file(int file_link,int* status);





/*@assgined to Kacper*/
//int check_line_format(char* input_line);

/** @brief Function splits string to array of strings that representing particular objects
 *
 * @param input_line line that will be converted to array of strings
 * @param number_of_words number of words that array will contain
 * @param separator words separator
 * @return array of strings
 * @author Krzysztof Funkowski
 */
char ** split(char* input_line, int number_of_words, char separator);

/** @brief Function splits string to array of strings that representing particular objects to represent command line struct
 *
 * @param input_line line that will be converted to array of strings
 * @return array of strings
 * @author Krzysztof Funkowski
 */
char ** split_command_line(char* input_line);

/**
 * @brief Function used to open input file for reading
 * @return int Value returned is file descriptor
 * @author Krzysztof Funkowski
 */
int open_read_file(const char* file_str);

//int convert_singleLine_to_struct();

//void sort_input_lines(char**);


/*
params are structs containing parsed command line
*/
//int compare_two_lines_based_on_time(                       );

#endif // FILE_INCLUDED

