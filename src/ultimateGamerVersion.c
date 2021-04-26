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
#include <syslog.h>
#include "start_lib.h"

int main()
{
    openlog("output", 0, LOG_USER);
    daemon2();
    syslog(LOG_NOTICE, "Daemon started.");
    int file,status=0,line_count=0,i,start_time;
    char* file_str = "testowy2.txt";
    char** splitted_array;
    if((file = open_read_file(file_str))==-1) 
    {
        syslog(LOG_NOTICE, "Daemon failed. File not found.");
        closelog();
        close(file);
        return EXIT_FAILURE;
    }
    
    command_array array;
    init_command_struct_array(&array,10);

    thread_array threads;

    singleLine* sl = NULL;
    syslog(LOG_NOTICE, "Daemon get to while.");
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
        sl=NULL;
    }
    syslog(LOG_NOTICE, "Daemon get past while.");
    quicksort(&array,0,array.size_current-1);
    merge_times_to_one_timeline(&array);
    array.command_entity[0]->time -= 60;
    init_thread_array(&threads,array.size_current);
    i = 0;
    syslog(LOG_NOTICE, "Daemon get to for.");
    for(i=0;i<array.size_current;i++)
    {
        pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        //printf("%s %s %d %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time,command_count_words(array.command_entity[i]->command));
    }
    syslog(LOG_NOTICE, "Daemon get past for.");
    pthread_exit(NULL);
    free(array.command_entity);
    free(threads.tid);
    
    close(file);
    syslog(LOG_NOTICE, "Daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}