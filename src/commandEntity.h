 /**
 * @file commandEntity.h
 * @author Krzysztof Funkowski
 * @brief Representation of command entity and command entity functionalities
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef COMMANDENTITY_H_INCLUDED
#define COMMANDENTITY_H_INCLUDED


/** \brief Structure of command entity
 */
typedef struct {
int time;
char* command;
char* parameter;
}command_struct;

/** \brief Structure of array of command entity
 */
typedef struct {
    command_struct** command_entity;
    int size_current;
    int size_max;
}command_array;

/** \brief Allocating memory for new command entity, then parsing array of strings to command entity.
 *
 * \param splitted_command_line array of strings to parse into command entity
 * \return pointer to converted command entity
 *
 */
command_struct* convert_command_to_struct(char** splitted_command_line);


/** \brief Get the remaining time to execute the command
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 *
 */
int remaining_time_to_execution(command_struct* command_line);

void init_command_struct_array(command_array *array, int size);

command_struct** extend_command_line_array(command_array* array, int size);

void free_command(command_struct* command);

void swap(command_struct* x, command_struct* y);

void quicksort(command_array *array,int lewy,int prawy);

void merge_times_to_one_timeline(command_array* array);

void correct_first_time(command_array* array);

#endif // COMMANDENTITY_H_INCLUDED
