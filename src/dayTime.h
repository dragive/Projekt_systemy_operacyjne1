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


/** \brief Get current time in seconds.
 *
 * \return time in seconds
 * \author KF
 */
int get_time_in_sec();

/** \brief Get seconds to full minute from now.
 * \param time Time to next commands iteration
 * \return time in seconds to full minute
 * \author KF
 */
int get_time_to_full_minute();

/** \brief Get time to next commands iteration in loop.
 * \param time Start time of a program.
 * \return remaining time to next iteration in seconds
 * \author KF
 */
int get_time_to_next_iteration();

#endif // DAYTIME_H_INCLUDED
