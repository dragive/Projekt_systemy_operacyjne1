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
    command_line->time=temp*60*60;
    sscanf(splitted_command_line[1],"%d",&temp);
    command_line->time+=temp*60;
    command_line->time=remaining_time_to_execution(command_line);
    command_line->command = (char*)malloc((strlen(splitted_command_line[2])+1)*sizeof(char));
    strcpy(command_line->command,splitted_command_line[2]);
    command_line->parameter = (char*)malloc((strlen(splitted_command_line[3])+1)*sizeof(char));
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

void init_command_struct_array(command_array* array, int size)
{
    array->command_entity = (command_struct**)malloc(size*sizeof(command_struct*));
    array->size_current=0;
    array->size_max=size;
}

//DO POPRAWKI
command_struct** extend_command_line_array(command_array* array,int size)
{
    array->size_max;
    int new_size_max=array->size_max+size;
    command_struct** new = (command_struct**)malloc((new_size_max)*sizeof(command_struct*));
    int i=0;
    for(i=0;i<array->size_max;i++)
    {
        new[i] = (command_struct*)malloc(sizeof(command_struct));
        new[i]->command = (char*)malloc(strlen(array->command_entity[i]->command)+1);
        new[i]->parameter = (char*)malloc(strlen(array->command_entity[i]->parameter)+1);
        strcpy(new[i]->command,array->command_entity[i]->command);
        strcpy(new[i]->parameter,array->command_entity[i]->parameter);
        new[i]->time=array->command_entity[i]->time;
    }
    free(array->command_entity);
    array->command_entity=NULL;
    array->size_max=new_size_max;
    return new;
}

/** \brief Using to free memory
 *
 * \param command_line command entity pointer to free
 * \author KF
 */
void free_command(command_struct* command)
{
    if(command->command!=NULL) free(command->command);
    if(command->parameter!=NULL) free(command->parameter);
    free(command);
}

void swap(command_struct* x, command_struct* y)
{
    command_struct temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void quicksort(command_array *array,int lewy,int prawy)
{
    int os=array->command_entity[(lewy+prawy)/2]->time;
    int p,q;
    p=lewy;
    q=prawy;
    do{
        while (array->command_entity[p]->time<os) p++;
        while (array->command_entity[q]->time>os) q--;
        if(p<=q)
        {
            swap(array->command_entity[p],array->command_entity[q]);
            p++;
            q--;
        }
    }while(p<=q);

    if(q>lewy) quicksort(array,lewy,q);
    if(p<prawy) quicksort(array,p,prawy);
}

void merge_times_to_one_timeline(command_array* array)
{
    int i;
    int time_sum=0;
    int flag=0;
    for(i=0;i<array->size_current;i++)
    {
        if(array->command_entity[i]->time > 0 && flag == 1)
        {
            array->command_entity[i]->time = array->command_entity[i]->time - time_sum;
            time_sum += array->command_entity[i]->time;
        }
        else if(array->command_entity[i]->time > 0 && flag == 0)
        {
            time_sum += array->command_entity[i]->time;
            flag=1;
        }
    }
}