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

/**
 * @brief Struct representing single line read from file.
 *
 */
typedef struct
{
    char * value;    /** Pointer to table of chars read from file */
    int size_max;               /** Max size which can be currently stored */
    int size_current;           /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
}singleLine;

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
#endif // SINGLELINE_INCLUDED
