/**
 * @file singleLine.h
 * @author Maciej Fender
 * @brief singleLine is meant to handle reading line from file
 * @version 0.1
 * @date 2021-03-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef SINGLELINE_INCLUDED
#define SINGLELINE_INCLUDED

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Struct representing single line read from file.
 *
 */
typedef struct singleLine singleLine;

/** \brief Function adds character to singleLine
 *
 * \param sl singleLine struct object which line will be written to from file
 * \param c character which will be added to singleLine
 * \author MF
 */
void add_char_to_singleLine(singleLine * sl,char c);


/** \brief Function extends buffor in single line
 *
 * \param sl singleLine struct object which buffor will be extended
 * \author MF
 */
void extend_buffor_singleLine(singleLine* sl);

int singleLine_get_size_max(singleLine* sl);

int singleLine_get_size_current(singleLine* sl);

char* singleLine_get_value(singleLine* sl);


#endif // SINGLELINE_INCLUDED