/**
 * @file filehandleTest.c
 * @author Krzysztof Funkowski
 * @brief File for testing functionalities
 * @version 0.1
 * @date 2021-03-22
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






int main(int argc, char** argv)
{
    int file,status=0,line_count=0,i;
    char* file_str = "testowy.txt";
    char** splitted_array;
    pthread_t tid[6];
    if((file = open_read_file(file_str))==-1) return -1;
    
    command_array array;
    init_command_struct_array(&array,10);

    singleLine* sl = NULL;
    while(status==0)
    {
        sl = get_line_from_file(file,&status);
        if(sl != NULL) 
        {
            splitted_array=split_command_line(sl->value);
            //printf("SIZE: %d\n",array.size_current);
            if(array.size_current==array.size_max) {array.command_entity=extend_command_line_array(&array,5);}
            array.command_entity[array.size_current++]=convert_command_to_struct(splitted_array);
        }
        free(sl);
    }

    for(i=0;i<array.size_current;i++)
    {
        //pthread_create(&tid[i],NULL,threading_func,array.command_entity[i]);
        printf("%s %s %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time);
    }
    pthread_exit(NULL);
    /*for(i=0;i<array.size_max;i++)
    {
        free_command(array.command_entity[i]);
    }*/
    free(array.command_entity);
    close(file);
    return 0;
}
