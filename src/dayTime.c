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

/** \brief Get current time in seconds.
 *
 * \return time in seconds
 * \author KF
 */
int get_time_in_sec()
{
    struct timeval tv;
    struct tm *current_time;
    time_t t;
    gettimeofday(&tv, NULL);

    //get seconds from timer
    t = tv.tv_sec;

    //get current time
    current_time = localtime(&t);

    //return hours and minutes converted to seconds
    return current_time->tm_hour*60*60+current_time->tm_min*60;
}

/** \brief Get seconds to full minute from now.
 * \param time Time to next commands iteration
 * \return time in seconds to full minute
 * \author KF
 */
int get_time_to_full_minute(int time)
{
    return time%60;
}

/** \brief Get time to next commands iteration in loop.
 * \param time Start time of a program.
 * \return remaining time to next iteration in seconds
 * \author KF
 */
int get_time_to_next_iteration(int start_time)
{
    struct timeval tv;
    struct tm *current_time;
    time_t t;
    gettimeofday(&tv, NULL);
    t = tv.tv_sec;

    //get current time
    current_time = localtime(&t);

    //Subtract current time from number of seconds in day and add time in seconds of an start time
    return 86400 - current_time->tm_hour*60*60 - current_time->tm_min*60 - current_time->tm_sec + start_time;
}
