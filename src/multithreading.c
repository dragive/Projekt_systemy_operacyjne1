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
#include "file.h"
#include "commandEntity.h"

void init_thread_array(thread_array* array, int size)
{
    array->tid = (pthread_t*)malloc(size*sizeof(pthread_t));
    array->size_current=0;
    array->size_max=size;
}

void* threading_func(void* vargp)
{
    int i,pid,count;
    command_struct* command = (command_struct*)vargp;
    count=command_count_words(command->command);
    char** string_array=split(command->command,count,' ');

    //char *args[] = {string_array[0],string_array[1],NULL};
    char **args = (char**)malloc((count+1)*sizeof(char*));
    for(i = 0; i < count ; i++)
    {
        args[i] = (char*)malloc((strlen(string_array[i])+1)*sizeof(char));
        strcpy(args[i],string_array[i]);
    }
    args[i]=NULL;
    pid = fork();
    if(pid == 0)
    {
        int fp = open("wynik.txt", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
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

int command_count_words(char* input)
{
    int n = strlen(input);
    //printf("1");
    int ret= 0;
    for(int i =0;i<n&&input[i]!='\0';i++){
            //printf("1");
        if(ret==0){if(input[i]!=' ')ret=1;continue;}
        //printf("1");
        if(input[i]==' '){
                //printf("2");
                while(i<n&&input[i]==' '&&input[i]!='\0'){
                    i++;continue;
                }
        //printf("3");
                if(i<n&&input[i]!=' '&&input!='\0'){ret++;}

        }
    }
    return ret;
}