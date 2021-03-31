/**
 * @file commandEntity.c
 * @author Krzysztof Funkowski
 * @brief Representation of command entity and command entity functionalities
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "commandEntity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dayTime.h"

struct command_struct
{
    int time;
    char *command;
    char *parameter;
};

/** \brief Allocating memory for new command entity, then parsing array of strings to command entity.
 *
 * \param splitted_command_line array of strings to parse into command entity
 * \return pointer to converted command entity
 *
 */
command_struct* convert_command_to_struct(char** splitted_command_line)
{
    command_struct* command_line = (command_struct*)malloc(sizeof(command_struct));
    int temp;
    sscanf(splitted_command_line[0],"%d",&temp);
    command_line->time=temp*60;
    sscanf(splitted_command_line[1],"%d",&temp);
    command_line->time+=temp;
    command_line->command = (char*)malloc(strlen(splitted_command_line[2])*sizeof(char)+1);
    strcpy(command_line->command,splitted_command_line[2]);
    command_line->parameter = (char*)malloc(strlen(splitted_command_line[3])*sizeof(char)+1);
    strcpy(command_line->parameter,splitted_command_line[3]);
    return command_line;
}

/** \brief Get the remaining time to execute the command
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 *
 */

int remaining_time_to_execution(command_struct* command_line)
{
    int temp = command_line->time - get_time_in_sec();
    return (temp>=0)?temp:-1;
}

int command_get_time(command_struct* command_line)
{
    return command_line->time;
}

char* command_get_command(command_struct* command_line)
{
    return command_line->command;
}

char* command_get_parameter(command_struct* command_line)
{
    return command_line->parameter;
}

void free_command(command_struct* command)
{
    free(command->command);
    free(command->parameter);
    free(command);
}
