/**
 * @file dayTime.h
 * @author Krzysztof Funkowski
 * @brief File to convert time
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef MULTITHREADING_H_INCLUDED
#define MULTITHREADING_H_INCLUDED

#include <pthread.h>

typedef struct {
    pthread_t* tid;
    int size_current;
    int size_max;
}thread_array;

/** \brief Threading function
 */
void* threading_func(void* vargp);

void* write_remaining_to_file(void* vargp);

void init_thread_array(thread_array* array, int size);

int command_count_words(char* input,char sep);

#endif // MULTITHREADING_H_INCLUDED
