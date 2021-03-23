/**
 * @file main.c
 * @author Maciej Fender
 * @brief Main file of the program
 * @version 0.1
 * @date 2021-03-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "singleLine.h"
/**
 * @brief Global variable storing name of input file
 */
char* input_file;
/**
 * @brief Global variable storing name of output file
 */
char* output_file;

/**
 * @brief Function gets arguments from start of the program, validate and assigns to propriete global variable.
 *
 * @param argc Number of arguments
 * @param argv The array of arguments.
 * @return int Indicator whether process of parsing arugments gone well. When it's ok then 0, else something gone wrong.
 * @author MF
 */
int parse_arguments(int argc, char *argv[]){
    if( argc < 3 ) {
        return 3-argc;
    }
    else if (argc >3){
        return argc;
    }
    else{
        strcpy(input_file,argv[1]);
        strcpy(output_file,argv[2]);
    }
    return 0;

}


int remaining_time_to_execution(command_struct* command_line)
{
    int temp = command_line->time - get_time_in_sec();
    return (temp>=0)?temp:-1;
}

int main(int argc, char *argv[]){
    get_new_character_from_file(2137);

}
