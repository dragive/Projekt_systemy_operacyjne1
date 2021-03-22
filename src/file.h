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
#ifndef SINGLELINE_INCLUDED
#define SINGLELINE_INCLUDED


#include <unistd.h>
#include "singleLine.h"


/**
 * @brief Function used to open input file for reading
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @author MF
 */
int open_to_read_file(const char *  file_name);
/**
 * @brief Function used to open output file for appending
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @see open_to_read_input_file()
 * @author MF
 */
int open_to_append_file(const char *  file_name);

/** \brief Read line from file
 *
 * \param Line struct to which characters will be written
 * \param File which characters are read from
 * \return Array of characters read from file
 * \author MF
 */
char* get_line_from_file(int file_link);

/**
 * @brief Get the new character from file
 *
 * @param file File which character will be read from
 * @return char Character read from file
 */
char get_new_character_from_file(int file);

/** \brief Read line from file
 *
 * \param line Line struct to which characters will be written
 * \param file File which characters are read from
 * \return Array of characters read from file
 * \author MF
 */
char* get_line_from_file(singleLine *line,int file);

/*@assgined to Kacper*/
int check_line_format(char* input_line);

/*Krzysiek i struct*/
char ** split_command_line(char* input_line);

int convert_singleLine_to_struct();

void sort_input_lines(char**);


/*
params are structs containing parsed command line
*/
int compare_two_lines_based_on_time(                       );

#endif // SINGLELINE_INCLUDED

