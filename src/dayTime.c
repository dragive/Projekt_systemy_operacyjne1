/**
 * @file dayTime.c
 * @author Krzysztof Funkowski
 * @brief File to convert time
 * @version 0.1
 * @date 2021-03-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "dayTime.h"

/** \brief Get current time in seconds
 * \return time in seconds
 */

int get_time_in_sec()
{
    struct timeval tv;
    struct tm *current_time;
    time_t t;
    gettimeofday(&tv, NULL);
    t = tv.tv_sec;
    current_time = localtime(&t);
    return current_time->tm_hour*60+current_time->tm_min;
}

//testing
int get_time_to_full_minute()
{
    struct timeval tv;
    struct tm *current_time;
    time_t t;
    gettimeofday(&tv, NULL);
    current_time = localtime(&t);
    return 60 - current_time->tm_sec;
}

int get_time_to_next_iteration(int start_time)
{
    struct timeval tv;
    struct tm *current_time;
    time_t t;
    gettimeofday(&tv, NULL);
    t = tv.tv_sec;
    current_time = localtime(&t);
    return 86400 - current_time->tm_hour*60*60 - current_time->tm_min*60 - current_time->tm_sec + start_time;
}
