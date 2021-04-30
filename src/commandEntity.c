/**
 * @file commandEntity.c
 * @author Krzysztof Funkowski
 * @brief Representation of command entity and command entity functionalities
 * @version 1.0
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
 * \author KF
 *
 */
command_struct* convert_command_to_struct(char** splitted_command_line)
{
    //allocate memory for new command entity
    command_struct* command_line = (command_struct*)malloc(sizeof(command_struct));
    int temp;
    //convert array of strings to particular values of command entity
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

/** \brief Get the remaining time to execute the command in secounds. If invoke of command is set to time before start of program, set time to -1.
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 * \author KF
 *
 */
int remaining_time_to_execution(command_struct* command_line)
{
    //substract execution time from current time
    int temp = command_line->time - get_time_in_sec();
    return (temp>=0)?temp:-1;
}

/** \brief Initializing struct that contains an array of command entity.
 *
 * \param array Array of command entities.
 * \param size Current max size of an array.
 * \author KF
 *
 */
void init_command_struct_array(command_array* array, int size)
{
    array->command_entity = (command_struct**)malloc(size*sizeof(command_struct*));
    array->size_current=0;
    array->size_max=size;
}

/** \brief Extending number of elements in struct.
 *
 * \param array Array of command entities.
 * \param size Describes amount of element for extend and array.
 * \author KF
 *
 */
command_struct** extend_command_line_array(command_array* array,int size)
{
    //set new max size of an array
    int new_size_max=array->size_max+size;
    //create new array
    command_struct** new = (command_struct**)malloc((new_size_max)*sizeof(command_struct*));
    int i=0;
    //copy values from old array to new one
    for(i=0;i<array->size_max;i++)
    {
        new[i] = (command_struct*)malloc(sizeof(command_struct));
        new[i]->command = (char*)malloc(strlen(array->command_entity[i]->command)+1);
        new[i]->parameter = (char*)malloc(strlen(array->command_entity[i]->parameter)+1);
        strcpy(new[i]->command,array->command_entity[i]->command);
        strcpy(new[i]->parameter,array->command_entity[i]->parameter);
        new[i]->time=array->command_entity[i]->time;
    }
    //free old array
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

/** \brief Swapping command entities with eachother
 *
 * \param x command entity pointer to swap
 * \param y command entity pointer to swap
 * \author KF
 */
void swap(command_struct* x, command_struct* y)
{
    command_struct temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/** \brief Function for sorting command entities in order by remaining time to execution. Function is using quicksort alghoritm.
 *
 * \param array array of command entities
 * \param left left beginning of the interval
 * \param right left beginning of the interval
 * \author KF
 */
void quicksort(command_array *array,int lewy,int prawy)
{
    //choose pivot
    int os=array->command_entity[(lewy+prawy)/2]->time;
    int p,q;
    p=lewy;
    q=prawy;
    //quicksort algorithm
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

/** \brief Function for merging command entities times to one timeline to prevent incorrect time read.
 *
 * \param array array of command entities
 * \author KF
 */
void merge_times_to_one_timeline(command_array* array)
{
    int i;
    int time_sum=0;
    int flag=0;
    //search for first positive value time
    for(i=0;i<array->size_current;i++)
    {
        //if time is positive and flag equals to 1 than from current time subtract sum of times checked and in next step add this time to checked sum of time
        if(array->command_entity[i]->time > 0 && flag == 1)
        {
            array->command_entity[i]->time = array->command_entity[i]->time - time_sum;
            time_sum += array->command_entity[i]->time;
        }
        //add this time to checked sum of time and set flag to 1
        else if(array->command_entity[i]->time > 0 && flag == 0)
        {
            time_sum += array->command_entity[i]->time;
            flag=1;
        }
    }
}

/** \brief Correcting first positive number of time in entities to get correct timing in main.
 *
 * \param array array of command entities
 * \author KF
 */
void correct_first_time(command_array* array)
{
    int i;
    for(i=0;i<array->size_current;i++)
    {
        //if time of current command entity is between 0 and 59 than just break. We don't need to modify first time
        if(array->command_entity[i]->time>=0 && array->command_entity[i]->time<60) break;
        //if time is greater than 0  than subtract from time value 60 and break.
        else if(array->command_entity[i]->time>0)
        {
            array->command_entity[i]->time -= 60;
            break;
        }
    }
}