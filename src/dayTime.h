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
#ifndef DAYTIME_H_INCLUDED
#define DAYTIME_H_INCLUDED


/** \brief Get current time in seconds
 * \return time in seconds
 */
int get_time_in_sec();

int get_time_to_full_minute();

int get_time_to_next_iteration();

#endif // DAYTIME_H_INCLUDED
