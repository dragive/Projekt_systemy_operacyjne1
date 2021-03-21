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
#include <unistd.h>
#include <stdio.h>
#include "singleLine.h"

/**
 * @brief Struct representing single line read from file.
 *
 */
typedef struct singleLine
{
    char * pointer_to_value;    /** Pointer to table of chars read from file */
    int size_max;               /** Max size which can be currently stored */
    int size_current;           /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
} singleLine;


//#TODO
/*
add function to add
                realloc with bigger buffor (used in add function)

*/













/*
1. lista jednokierunkowa jako lista komend
    @assigned Krzysiek

2. listra structów
    czas rozpoczecia 12 30
    czas do dopalenia 3000 s
    structy
    parametr
     |
    \/
    czas rozpoczecia 12 31
    czas do dopalenia 60 s
    structy
    parametr
3. sortowanie listy komend wzgledem czasu
4.
*/

















