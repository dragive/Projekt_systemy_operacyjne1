/**
 * @file multitreading.c
 * @author Krzysztof Funkowski
 * @brief Multithreading, pipes and writing remaining tasks to logs
 * @version 1.0
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

/** \brief Function used in threading to parse command to exec in async way.
 *
 * \param vargp it's a pointer of command entity
 * \author MF & KF
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
        for(i=0;i<count;i++)
        {
            free(string_array[i]);
        }
        free(string_array);

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
            execvp(args[0],args);
            exit(0);
        }
        else
        {
            //wait for the child
            wait(NULL);
        }
    }
    /// case when there's char | in input command, thus there's need to create
    else
    {   ///splitting commands by |
        int last_pipe;
        int pipes[2];
        char** strings = split(command->command,count_pipes+1,'|');
        char** string_array;
        char** args;
        int j,count_words,current_pipe=0;
        int** fd = (int**)malloc((count_pipes+1)*sizeof(int*));

        /// creating pipes for the first subcommand
        pipe(pipes);
        /// how many words are in the single subcommand
        count_words = command_count_words(strings[0],' ');
        /// spiting subcommands by spaces
        string_array = split(strings[0],count_words,' ');
        /// allocating memory to args
        args = (char**)malloc((count_words+1)*sizeof(char*));
        ///initializing args 
        for(j = 0; j < count_words ; j++)
        {
            args[j] = (char*)malloc((strlen(string_array[j])+1)*sizeof(char));
            strcpy(args[j],string_array[j]);
        }
        pid = fork();
       
        if(pid == 0) ///child
        { 
            close(pipes[0]); //closing output side
            ///setting output
            dup2(pipes[1],1); 
            close(pipes[1]); 
            /// executing subcommand
            execvp(args[0],args);
        }
     
        close(pipes[1]);
        last_pipe = pipes[0];

        /// loop where from 2 to penultimate
        for(int y =1; y < count_pipes; y++){
            //syslog(LOG_NOTICE,"%s",strings[y]);
            /// creating pipes
            pipe(pipes);
            /// counting words for subcommands
            count_words = command_count_words(strings[y],' ');
            /// split by spaces
            string_array = split(strings[y],count_words,' ');
            args = (char**)malloc((count_words+1)*sizeof(char*));
            for(j = 0; j < count_words ; j++)
            {
                args[j] = (char*)malloc((strlen(string_array[j])+1)*sizeof(char));
                strcpy(args[j],string_array[j]);
            }
            pid = fork();
            if(pid == 0) 
            { 
                ///assigning last pipe from pervious sub command output to this one
                dup2(last_pipe,0);
                close(last_pipe);
                /// forwarding output to nex pipe
                dup2(pipes[1], 1); 
                close(pipes[1]); 
                ///executing command
                execvp(args[0],args);
            }
            close(last_pipe);
            close(pipes[1]);
            last_pipe=pipes[0];
        }
        /// couting spaces
        count_words = command_count_words(strings[count_pipes],' ');
        /// spliting by spaces
        string_array = split(strings[count_pipes],count_words,' ');
        args = (char**)malloc((count_words+1)*sizeof(char*));
        for(j = 0; j < count_words ; j++)
        {
            args[j] = (char*)malloc((strlen(string_array[j])+1)*sizeof(char));
            strcpy(args[j],string_array[j]);
        }
        pid = fork();
        int fp = open(get_output_file_name(), O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
       
        if(pid == 0) 
        { 
            /// redirecting outout of previous subcommand to this, last one
            dup2(last_pipe, 0);
            close(last_pipe); 
            /// forwarding output to place defined by user
            if((strcmp(command->parameter,"1")==0)) dup2(fp,1);
            if((strcmp(command->parameter,"2")==0)) dup2(fp,2);
            if((strcmp(command->parameter,"3")==0)) 
            {
                dup2(fp,1);
                dup2(fp,2);
            }
            ///executing order
             execvp(args[0],args);
        }
        close(pipes[1]);
        last_pipe = pipes[0];
        close(fp);
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
 * \author MF
 *
 */
int command_count_words(char* input,char sep)
{
    //get length of an input
    int n = strlen(input);
    ///initializing returned value
    int ret = 0; 
    ///iterating through string until end
    for(int i =0;i<n&&input[i]!='\0';i++){
        ///if it is the first word, set ret to 1 and continue
        if(ret==0){if(input[i]!=sep)ret=1;continue;}
        /// separator is reached
        if(input[i]==sep){
                /// if separator is duplicated 
                while(i<n&&input[i]==sep&&input[i]!='\0'){
                    i++;continue;
                }
                /// if new character diffrent from separator is reached
                if(i<n&&input[i]!=sep&&input!='\0'){ret++;}

        }
    }
    return ret;
}