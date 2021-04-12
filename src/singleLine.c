/**
 * @file singleLine.c
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
#include <stdlib.h>
#include "singleLine.h"


/** \brief Function extends buffor in single line
 *
 * \param sl singleLine struct object which buffor will be extended
 * \author MF
 */
void extend_buffor_singleLine(singleLine* sl){
    char * temp = (char* ) malloc(sizeof(char)*sl->size_max+10);
    for(int i = 0;i<sl->size_max;i++){
        temp[i] = sl->value[i];
    }
    free(sl->value);
    sl->value = temp;
    sl->size_max += 10;
}
/** \brief Function adds character to singleLine
 *
 * \param sl singleLine struct object which line will be written to from file
 * \param c character which will be added to singleLine
 * \author MF
 */
void add_char_to_singleLine(singleLine * sl,char c){
    if(sl == NULL){
        sl = (singleLine*) malloc(sizeof(singleLine));
    }
    if(sl->value == NULL){
        sl->size_max = 10;
        sl->size_current = 0;
        sl->value = (char*) malloc(sizeof(char)*sl->size_max);
        sl->value[sl->size_current]='\0';
    }
    if(sl->size_current ==  sl->size_max-1){
        extend_buffor_singleLine(sl);
    }
    sl->value[sl->size_current++] = c;
    sl->value[sl->size_current] = '\0';
}

