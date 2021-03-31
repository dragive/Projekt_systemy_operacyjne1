/**
 * @file functionalitiesTest.c
 * @author Krzysztof Funkowski
 * @brief File for testing functionalities
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dayTime.h"
#include "commandEntity.h"

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



/**
 * @brief Function initialized when program starts. Just for testing things.
 *
 * @param argc Number of arguments
 * @param argv The array of arguments.
 * @return int Indicator whether process of parsing arugments gone well. When it's ok then 0, else something gone wrong.
 * @author Krzysztof Funkowski
 */
int main(int argc, char** argv)
{
    int i;
    char *str="21:30:dupadupadupa:3";
    command_struct* command_line;
    char **tab;
    tab = split_command_line(str);
    command_line = convert_command_to_struct(tab);
    for(i=0;i<4;i++)
    {
        printf("%s\n",tab[i]);
    }
    printf("%d %s %s %d\n",command_get_time(command_line),command_get_command(command_line),command_get_parameter(command_line),remaining_time_to_execution(command_line));

    for(i=0;i<4;i++)
    {
        free(tab[i]);
    }
    free(tab);
    free_command(command_line);
    return 0;
}
