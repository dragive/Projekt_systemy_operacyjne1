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

//global variables
int i;
int file;
//declare of command entities array
command_array array;

/** \brief Opening file descriptor, handling errors, getting lines from file, converting and parsing them to command entity format and running in proper time.
 *
 * \return If error occurs than return 1, if not return 0
 * \author KF
 *
 */
int initialize()
{
    int status=0,line_count=0,start_time,j;

    //get input file
    char* file_str = get_input_file_name();
    char** splitted_array;
    i = 0;

    //open file
    //if error occurs than write notice in log about file not found
    if((file = open_read_file(file_str))==-1) 
    {
        syslog(LOG_NOTICE, "Daemon failed. File not found.");

        //close file and log
        closelog();
        close(file);

        //return 1 when error occurs
        return EXIT_FAILURE;
    }
    
    //initialize array of command entities
    init_command_struct_array(&array,10);

    //declare of threads array
    thread_array threads;

    //singleLine for taking a line from file
    singleLine* sl = NULL;
    //read line by line in loop until EOF occurs(status==1)
    while(status==0)
    {
        //get line from file
        sl = get_line_from_file(file,&status);
        //if sl contains line
        if(sl != NULL) 
        {
            //split line to array of commands
            splitted_array=split_command_line(sl->value);
            
            //max size of an array is reached than extend size of an array
            if(array.size_current==array.size_max) {array.command_entity=extend_command_line_array(&array,5);}
            
            //convert 
            array.command_entity[array.size_current++]=convert_command_to_struct(splitted_array);

            //free space
            free(sl->value);
            free(sl);
            free(splitted_array[0]);
            free(splitted_array[1]);
            free(splitted_array[2]);
            free(splitted_array[3]);
            free(splitted_array);
            sl=NULL;
        }
    }

    //sort commands by execution time
    quicksort(&array,0,array.size_current-1);

    //merge to one timeline
    merge_times_to_one_timeline(&array);

    //correct first command entity with positive number
    correct_first_time(&array);

    //initialize array of threads
    init_thread_array(&threads,array.size_current);

    //get current time
    start_time =  get_time_in_sec();

    //sleep to full minute
    sleep(get_time_to_full_minute(get_time_to_next_iteration(start_time)));

    //running thread for commands
    while(1)
    {
        //command to run
        if(array.command_entity[i]->time>=0)
        {
            sleep(array.command_entity[i]->time);
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        } 
        i++;

        //if all commands executed
        if(i==array.size_current)
        {
            //break;
            //wait to next day to iterate over commands again
            sleep(get_time_to_next_iteration(start_time));
            i=0;
        }
    }
    /*for(i=0;i<array.size_current;i++)
    {
        if(array.command_entity[i]->time>=0) 
        {
            sleep(array.command_entity[i]->time);
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        }
        //printf("%s %s %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time);
    }*/

    //free space
    free(array.command_entity);
    free(threads.tid);
    pthread_exit(NULL);

    //return 0 when everything succeded
    return EXIT_SUCCESS;
}

/** \brief Function for signal handle
 *
 * \author KF
 *
 */
void sig_handler(int signum)
{
    //if SIGINT was sent to process
    if(signum == SIGINT)
    {
        //write log
        syslog(LOG_NOTICE, "Daemon catch Ctrl+C");

        //kill process
        kill(getpid(),SIGKILL);
    }
    //if SIGUSR1 was sent to process
    else if(signum == SIGUSR1)
    {
        //close file
        close(file);

        //fork
        int pid = fork();

        //re register signals
        signal(SIGUSR2,SIG_DFL);
        signal(SIGUSR2,sig_handler);
        signal(SIGUSR1,SIG_DFL);
        signal(SIGUSR1,sig_handler);
        //if child
        if(pid == 0)
        {
            syslog(LOG_NOTICE, "PID:%d Daemon started.",getpid());
            int init_status=initialize();
            if(init_status==EXIT_FAILURE) exit(1);
            syslog(LOG_NOTICE, "PID:%d Daemon terminated.",getpid());
        }
        //if parent
        else
        {
            //write log
            syslog(LOG_NOTICE, "PID:%d Daemon terminated.",getpid());

            //kill process
            kill(getpid(),SIGKILL);
        }
    }
    //if SIGURS2 was sent to process
    else if(signum == SIGUSR2)
    {
        //ignore SIGUSR2
        signal(SIGUSR2,SIG_IGN);
        pthread_t tid;
        //run tread that will be writing remaining files to execute
        pthread_create(&tid,NULL,write_remaining_to_file,&array);
    }
}

int main(int argc, char** argv)
{
    //openlog
    openlog("minicron", 0, LOG_USER);

    //check and parse parameteres
    int file_status=parse_arguments(argc,argv);
    
    //if there is too few files
    if(file_status>=1 && file_status <=2)
    {
        printf("Podales o %d mniej argumentow niz powinienes!\n",file_status);
        printf("Prawidlowy format: sciezka_pliku_daemon sciezka_pliku_wejsciowego sciezka_pliku_wynikowego\n");
        syslog(LOG_NOTICE, "Uzytkownik podal za malo argumentow.");
        return EXIT_FAILURE;
    }
    //if there is too many files
    if(file_status>=3)
    {
        printf("Podales za duzo argumentow!\n");
        printf("Prawidlowy format: sciezka_pliku_daemon sciezka_pliku_wejsciowego sciezka_pliku_wynikowego\n");
        syslog(LOG_NOTICE, "Uzytkownik podal za duzo argumentow.");
        return EXIT_FAILURE;
    }

    //register signals
    signal(SIGINT,sig_handler);
    signal(SIGUSR1,sig_handler);
    signal(SIGUSR2,sig_handler);

    //start daemon
    daemon2();

    //write startlog
    syslog(LOG_NOTICE, "PID:%d Daemon started.",getpid());

    //initialize file opening and command handle
    int init_status=initialize();

    //if error occurs exit program
    if(init_status==EXIT_FAILURE) EXIT_FAILURE;

    //write endlog
    syslog(LOG_NOTICE, "PID:%d Daemon terminated.",getpid());
    pthread_exit(NULL);

    //close file and logs
    close(file);
    closelog();

    //exit succeed
    return EXIT_SUCCESS;
}