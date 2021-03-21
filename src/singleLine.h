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
typedef struct singleLine
{
    char * pointer_to_value;    /** Pointer to table of chars read from file */
    int size_max;               /** Max size which can be currently stored */
    int size_current;           /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
};

#endif // SINGLELINE_INCLUDED
