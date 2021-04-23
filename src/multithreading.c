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

void* threading_func(void* vargp)
{
    int pid;
    command_struct* command = (command_struct*)vargp;
    char** string_array=split(command->command,2,' ');
    char ch[1];
    /*sscanf(string_array[1],"%d",&i);
    printf("i: %d\n",i);
    i=5;
    sprintf(ch,"%d",i);*/
    char *args[] = {string_array[0],string_array[1],NULL};
    pid = fork();
    if(pid == 0)
    {
        execvp(string_array[0],args);
        exit(0);
    }
    else
    {
        wait(NULL);
    }
}