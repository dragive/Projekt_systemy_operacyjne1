/**
 * @file commandEntity.h
 * @author Krzysztof Funkowski
 * @brief Representation of command entity and command entity functionalities
 * @version 1.0
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
 * \author KF
 *
 */
command_struct* convert_command_to_struct(char** splitted_command_line);


/** \brief Get the remaining time to execute the command in secounds. If invoke of command is set to time before start of program, set time to -1.
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 * \author KF
 *
 */
int remaining_time_to_execution(command_struct* command_line);

/** \brief Initializing struct that contains an array of command entity.
 *
 * \param array Array of command entities.
 * \param size Current max size of an array.
 * \author KF
 *
 */
void init_command_struct_array(command_array *array, int size);

/** \brief Extending number of elements in struct.
 *
 * \param array Array of command entities.
 * \param size Describes amount of element for extend and array.
 * \author KF
 *
 */
command_struct** extend_command_line_array(command_array* array, int size);

/** \brief Using to free memory
 *
 * \param command_line command entity pointer to free
 * \author KF
 */
void free_command(command_struct* command);

/** \brief Swapping command entities with eachother
 *
 * \param x command entity pointer to swap
 * \param y command entity pointer to swap
 * \author KF
 */
void swap(command_struct* x, command_struct* y);

/** \brief Function for sorting command entities in order by remaining time to execution. Function is using quicksort alghoritm.
 *
 * \param array array of command entities
 * \param left left beginning of the interval
 * \param right left beginning of the interval
 * \author KF
 */
void quicksort(command_array *array,int lewy,int prawy);

/** \brief Function for merging command entities times to one timeline to prevent incorrect time read.
 *
 * \param array array of command entities
 * \author KF
 */
void merge_times_to_one_timeline(command_array* array);

/** \brief Correcting first positive number of time in entities to get correct timing in main.
 *
 * \param array array of command entities
 * \author KF
 */
void correct_first_time(command_array* array);

#endif // COMMANDENTITY_H_INCLUDED
