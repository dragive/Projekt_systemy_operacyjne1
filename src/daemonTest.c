/**
 * @file daemonTest.c
 * @author Krzysztof Funkowski
 * @brief File for testing functionalities
 * @version 0.1
 * @date 2021-04-22
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "file.h"
#include "commandEntity.h"
#include "multithreading.h"
#include "dayTime.h"


int main(int argc, char** argv)
{
    int file,status=0,line_count=0,i,start_time;
    char* file_str = "testowy2.txt";
    char** splitted_array;
    if((file = open_read_file(file_str))==-1) return -1;
    
    command_array array;
    init_command_struct_array(&array,10);

    thread_array threads;

    singleLine* sl = NULL;
    while(status==0)
    {
        sl = get_line_from_file(file,&status);
        if(sl != NULL) 
        {
            splitted_array=split_command_line(sl->value);
            if(array.size_current==array.size_max) {array.command_entity=extend_command_line_array(&array,5);}
            array.command_entity[array.size_current++]=convert_command_to_struct(splitted_array);
        }
        free(sl);
    }

    quicksort(&array,0,array.size_current-1);
    merge_times_to_one_timeline(&array);
    array.command_entity[0]->time -= 60;
    init_thread_array(&threads,array.size_current);
    i = 0;
    start_time =  get_time_in_sec();
    printf("%d\n=====================\n",start_time);
    printf("%d\n=====================\n",get_time_to_full_minute(get_time_to_next_iteration(start_time)));
    printf("%d\n=====================\n",get_time_to_next_iteration(start_time));
    sleep(get_time_to_full_minute(get_time_to_next_iteration(start_time)));
    while(1)
    {
        if(array.command_entity[i]->time>=0)
        {
            sleep(array.command_entity[i]->time);
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        }
        i++;
        if(i==array.size_current) break;
        //sleep(get_time_to_next_iteration(start_time));
    }

    /*for(i=0;i<array.size_current;i++)
    {
        pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        //printf("%s %s %d %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time,command_count_words(array.command_entity[i]->command));
    }*/
    pthread_exit(NULL);
    free(array.command_entity);
    close(file);
    return 0;
}