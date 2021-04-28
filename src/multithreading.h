/**
 * @file multitreading.h
 * @author Krzysztof Funkowski
 * @brief File to convert time
 * @version 0.1
 * @date 2021-03-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef MULTITHREADING_H_INCLUDED
#define MULTITHREADING_H_INCLUDED

#include <pthread.h>

/** \brief Structure of array of threads
 */
typedef struct {
    pthread_t* tid;
    int size_current;
    int size_max;
}thread_array;

/** \brief Function used in threading to parse command to exec in async way. [WILL BE CHANGED. NO NEED TO PUT THIS ANYWHERE KACPER]
 *
 * \param vargp it's a pointer of command entity
 * \author KF
 *
 */
void* threading_func(void* vargp);

/** \brief Funtion for writing to log remaining commands that has not been executed.
 *
 * \param vargp it's a pointer of command entity
 * \author KF
 *
 */
void* write_remaining_to_file(void* vargp);

/** \brief Initializing struct that contains an array of threads.
 *
 * \param array Array of command entities
 * \param size Current max size of an array
 * \author KF
 *
 */
void init_thread_array(thread_array* array, int size);

/** \brief Funtion for counting words separated by defined in sep variable separator. It check count of sep and return count + 1.
 *
 * \param input is a string that will be separated
 * \param sep user specified separator
 * \return number of words in command
 * \author MF
 *
 */
int command_count_words(char* input,char sep);

#endif // MULTITHREADING_H_INCLUDED
