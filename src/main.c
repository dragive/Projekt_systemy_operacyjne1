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

/** \brief Get the remaining time to execute the command
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 * \author Krzysztof Funkowski
 */
int remaining_time_to_execution(command_struct* command_line)
{
    int temp = command_line->time - get_time_in_sec();
    return (temp>=0)?temp:-1;
}

/** \brief Function splits string to array of strings that representing particular objects
 *
 * \param input_line line that will be converted to array of strings
 * \return array of strings
 */
char ** split_command_line(char* input_line)
{
    int i=0, length=0, word=0, words_count=4;
    char** str_tab = (char**)malloc(words_count*sizeof(char*));
    char* temp_str;
    for(i=0; i<words_count;i++)
    {
        str_tab[i] = (char*)malloc(strlen(input_line)*sizeof(char));
    }

    i=0;

    while(input_line[i]!='\0')
    {
        if(input_line[i]==':')
        {
            str_tab[word][length]='\0';
            //str_tab[word][length-1]='\0';
            /*temp_str=str_tab[word];
            memmove(temp_str,str_tab[word]+1,strlen(str_tab[word]));
            str_tab[word]=temp_str;*/
            word++;
            length=0;
        }
        else
        {
            str_tab[word][length]=input_line[i];
            length++;
        }
        i++;
    }
    str_tab[word][length]='\0';
    //str_tab[word][length-1]='\0';
    /*temp_str=str_tab[word];
    memmove(temp_str,str_tab[word]+1,strlen(str_tab[word]));
    str_tab[word]=temp_str;*/
    return str_tab;
}

int main(int argc, char *argv[]){
    get_new_character_from_file(2137);

}
