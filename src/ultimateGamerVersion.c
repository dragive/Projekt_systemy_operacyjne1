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
#include <signal.h>
#include "start_lib.h"

int i;

command_array array;

void correct_first_time(command_array* array)
{
    int i;
    for(i=0;i<array->size_current;i++)
    {
        if(array->command_entity[i]->time>=0 && array->command_entity[i]->time<60) break;
        else if(array->command_entity[i]->time>0)
        {
            array->command_entity[i]->time -= 60;
            break;
        }
    }
}


void sig_handler(int signum)
{
    if(signum == SIGINT)
    {
        syslog(LOG_NOTICE, "Daemon catch Ctrl+C");
        kill(getpid(),SIGKILL);
    }
    else if(signum == SIGUSR1)
    {

    }
    else if(signum == SIGUSR2)
    {
        signal(SIGUSR2,SIG_IGN);
        pthread_t tid;
        pthread_create(&tid,NULL,write_remaining_to_file,&array);
    }
}

int main()
{
    openlog("output", 0, LOG_USER);
    daemon2();
    syslog(LOG_NOTICE, "Daemon started.");
    signal(SIGINT,sig_handler);
    signal(SIGUSR1,sig_handler);
    signal(SIGUSR2,sig_handler);
    int file,status=0,line_count=0,start_time,j;
    char* file_str = "testowy2.txt";
    char** splitted_array;
    if((file = open_read_file(file_str))==-1) 
    {
        syslog(LOG_NOTICE, "Daemon failed. File not found.");
        closelog();
        close(file);
        return EXIT_FAILURE;
    }
    
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
    correct_first_time(&array);
    init_thread_array(&threads,array.size_current);
    i = 0;
    start_time =  get_time_in_sec();
    printf("%d\n=====================\n",getpid());
    printf("%d\n=====================\n",start_time);
    printf("%d\n=====================\n",get_time_to_full_minute(get_time_to_next_iteration(start_time)));
    printf("%d\n=====================\n",get_time_to_next_iteration(start_time));
    syslog(LOG_NOTICE, "Time to minute: %d",get_time_to_full_minute(get_time_to_next_iteration(start_time)));
    //sleep(get_time_to_full_minute(get_time_to_next_iteration(start_time)));
    syslog(LOG_NOTICE, "Daemon get to while2.");
    /*while(1)
    {
        if(array.command_entity[i]->time>=0)
        {
            sleep(array.command_entity[i]->time);
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        }
        i++;
        if(i==array.size_current) break;
        //sleep(get_time_to_next_iteration(start_time));
    }*/
    syslog(LOG_NOTICE, "Daemon get past while2.");
    syslog(LOG_NOTICE, "Daemon get to for.");
    for(i=0;i<array.size_current;i++)
    {
        if(array.command_entity[i]->time>=0) 
        {
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        }
        printf("%s %s %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time);
    }
    syslog(LOG_NOTICE, "Daemon get past for.");

    syslog(LOG_NOTICE, "Daemon terminated.");
    pthread_exit(NULL);
    free(array.command_entity);
    free(threads.tid);
    
    close(file);
    closelog();

    return EXIT_SUCCESS;
}