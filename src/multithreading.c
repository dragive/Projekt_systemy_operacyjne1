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

void init_thread_array(thread_array* array, int size)
{
    array->tid = (pthread_t*)malloc(size*sizeof(pthread_t));
    array->size_current=0;
    array->size_max=size;
}

void* threading_func(void* vargp)
{
    int i,pid,count,count_pipes;
    command_struct* command = (command_struct*)vargp;
    count=command_count_words(command->command,' ');
    count_pipes=command_count_words(command->command,'|')-1;
    if(count_pipes==0)
    {
        char** string_array=split(command->command,count,' ');
        char** args = (char**)malloc((count+1)*sizeof(char*));
        for(i = 0; i < count ; i++)
        {
            args[i] = (char*)malloc((strlen(string_array[i])+1)*sizeof(char));
            strcpy(args[i],string_array[i]);
        }
        args[i]=NULL;
        pid = fork();
        if(pid == 0)
        {
            int fp = open(get_output_file_name(), O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
            if((strcmp(command->parameter,"1")==0)) dup2(fp,1);
            if((strcmp(command->parameter,"2")==0)) dup2(fp,2);
            if((strcmp(command->parameter,"3")==0)) 
            {
                dup2(fp,1);
                dup2(fp,2);
            }
            close(fp);
            execvp(string_array[0],args);
            exit(0);
        }
        else
        {
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

void* write_remaining_to_file(void* vargp)
{
    command_array* array = (command_array*)vargp;
    extern int i;
    int j;
    for(j=i;j<array->size_current;j++)
    {
        syslog(LOG_NOTICE,"Remaining Task: %s",array->command_entity[j]->command);
    }
}

int command_count_words(char* input,char sep)
{
    int n = strlen(input);
    //printf("1");
    int ret= 0;
    for(int i =0;i<n&&input[i]!='\0';i++){
            //printf("1");
        if(ret==0){if(input[i]!=sep)ret=1;continue;}
        //printf("1");
        if(input[i]==sep){
                //printf("2");
                while(i<n&&input[i]==sep&&input[i]!='\0'){
                    i++;continue;
                }
        //printf("3");
                if(i<n&&input[i]!=sep&&input!='\0'){ret++;}

        }
    }
    return ret;
}