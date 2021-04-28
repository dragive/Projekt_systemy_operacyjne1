/**
 * @file multitreading.c
 * @author Krzysztof Funkowski
 * @brief File to convert time
 * @version 0.1
 * @date 2021-03-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "multithreading.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <syslog.h>
#include "file.h"
#include "commandEntity.h"
#include "start_lib.h"

/** \brief Initializing struct that contains an array of threads.
 *
 * \param array Array of command entities
 * \param size Current max size of an array
 * \author KF
 *
 */
void init_thread_array(thread_array* array, int size)
{
    array->tid = (pthread_t*)malloc(size*sizeof(pthread_t));
    array->size_current=0;
    array->size_max=size;
}

/** \brief Function used in threading to parse command to exec in async way. [WILL BE CHANGED. NO NEED TO PUT THIS ANYWHERE KACPER]
 *
 * \param vargp it's a pointer of command entity
 * \author KF
 *
 */
void* threading_func(void* vargp)
{
    int i,pid,count,count_pipes;
    command_struct* command = (command_struct*)vargp;

    //counting words in command overall
    count=command_count_words(command->command,' ');

    //counting commands separated by |
    count_pipes=command_count_words(command->command,'|')-1;

    //if there's no pipelines do this
    if(count_pipes==0)
    {
        //get splitted command into strings
        char** string_array=split(command->command,count,' ');
        char** args = (char**)malloc((count+1)*sizeof(char*));
        
        //parse this strings into arguments format for execvp.
        for(i = 0; i < count ; i++)
        {
            args[i] = (char*)malloc((strlen(string_array[i])+1)*sizeof(char));
            strcpy(args[i],string_array[i]);
        }

        //set the last element of arguements to NULL for program to know where agruments ends.
        args[i]=NULL;

        //fork to separate main process from child process where execvp will be running
        pid = fork();
        if(pid == 0)
        {
            //open output file
            int fp = open(get_output_file_name(), O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);

            //specify output of command
            if((strcmp(command->parameter,"1")==0)) dup2(fp,1);
            if((strcmp(command->parameter,"2")==0)) dup2(fp,2);
            if((strcmp(command->parameter,"3")==0)) 
            {
                dup2(fp,1);
                dup2(fp,2);
            }
            close(fp);

            //run execvp
            execvp(string_array[0],args);
            exit(0);
        }
        else
        {
            //wait for the child
            wait(NULL);
        }
    }
    else
    {
        char** strings = split(command->command,count_pipes+1,'|');
        char** string_array;
        char** args;
        int j,count_words,current_pipe=0;
        pid = fork();
        if(pid == 0)
        {
            for(i=0;i<count_pipes+1;i++)
            {
                count_words = command_count_words(strings[i],' ');
                string_array = split(strings[i],count_words,' ');
                args = (char**)malloc((count_words+1)*sizeof(char*));
                for(j = 0; j < count_words ; j++)
                {
                    args[j] = (char*)malloc((strlen(string_array[j])+1)*sizeof(char));
                    strcpy(args[j],string_array[j]);
                }
                args[j]=NULL;
                int* fd = (int*)malloc((count_pipes*2)*sizeof(int)); 
                for(j=0;j<count_pipes*2;j++)
                {
                    fd[j]=0;
                }
                pid_t pid2 = 0;
                pid_t pid3 = 0;
                if(pid3 = fork() == 0)
                {
                    for (int j = 0; j < count_pipes; j+=2) {
                        if (pid2 = fork() == 0) {
                            //child: make this cmd's output the other cmd's input
                            pipe(fd + (2*j) );
                            close(1);
                            dup(fd[j]);
                            if(j > 0) {
                                close(0);
                                dup(fd[j-1]);
                            }
                            execvp(string_array[0],args);
                            close(fd[j]);   
                            exit(0);        
                        }
                    }
                }
                else
                {
                    wait(NULL);
                    int fp = open("wynik.txt", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
                    dup2(fp,1);
                    close(fp);
                }
            }
        }
        else
        {
            wait(NULL);
        }
    }
}

/** \brief Funtion for writing to log remaining commands that has not been executed.
 *
 * \param vargp it's a pointer of command entity
 * \author KF
 *
 */
void* write_remaining_to_file(void* vargp)
{
    command_array* array = (command_array*)vargp;

    //get global i that points to next to currently executive command
    extern int i;
    int j;
    
    //for every non-executed command print it in log
    for(j=i;j<array->size_current;j++)
    {
        syslog(LOG_NOTICE,"Remaining Task: %s",array->command_entity[j]->command);
    }
}

/** \brief Funtion for counting words separated by defined in sep variable separator. It check count of sep and return count + 1.
 *
 * \param input is a string that will be separated
 * \param sep user specified separator
 * \return number of words in command
 * \author KF
 *
 */
int command_count_words(char* input,char sep)
{
    int n = strlen(input);
    int ret= 0;
    for(int i =0;i<n&&input[i]!='\0';i++){
        if(ret==0){if(input[i]!=sep)ret=1;continue;}
        if(input[i]==sep){
                while(i<n&&input[i]==sep&&input[i]!='\0'){
                    i++;continue;
                }
                if(i<n&&input[i]!=sep&&input!='\0'){ret++;}

        }
    }
    return ret;
}