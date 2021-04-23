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

//working
typedef struct {
    pthread_t* tid;
    int size_current;
    int size_max;
}thread_array;

void init_thread_array(thread_array* array, int size)
{
    array->tid = (pthread_t*)malloc(size*sizeof(pthread_t));
    array->size_current=0;
    array->size_max=size;
}

void swap(command_struct* x, command_struct* y)
{
    command_struct temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort(command_array* array)
{
    int i,j;
    for(i=0;i<array->size_current-1;i++)
    {
        for(j=0;j<array->size_current-i-1;j++)
        {
            if(array->command_entity[j]->time > array->command_entity[j+1]->time) swap(array->command_entity[j],array->command_entity[j+1]);
        }
    }
}

//testing
void quicksort(command_array *array,int lewy,int prawy)
{
    int os=array->command_entity[(lewy+prawy)/2]->time;
    int p,q;
    p=lewy;
    q=prawy;
    do{
        while (array->command_entity[p]->time<os) p++;
        while (array->command_entity[q]->time>os) q--;
        if(p<=q)
        {
            swap(array->command_entity[p],array->command_entity[q]);
            p++;
            q--;
        }
    }while(p<=q);

    if(q>lewy) quicksort(tab,lewy,q);
    if(p<prawy) quicksort(tab,p,prawy);
}

void merge_times_to_one_timeline(command_array* array)
{
    int i;
    int time_sum=0;
    int flag=0;
    for(i=0;i<array->size_current;i++)
    {
        if(array->command_entity[i]->time > 0 && flag == 1)
        {
            array->command_entity[i]->time = array->command_entity[i]->time - time_sum;
            time_sum += array->command_entity[i]->time;
        }
        else if(array->command_entity[i]->time > 0 && flag == 0)
        {
            time_sum += array->command_entity[i]->time;
            flag=1;
        }
    }
}

int main(int argc, char** argv)
{
    int file,status=0,line_count=0,i;
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

    bubble_sort(&array);
    merge_times_to_one_timeline(&array);
    init_thread_array(&threads,array.size_current);
    i=0;
    while(1)
    {
        if(array.command_entity[i]->time>=0)
        {
            sleep(array.command_entity[i]->time*60);
            pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        }
        i++;
        if(i==array.size_current) break;
    }

    /*for(i=0;i<array.size_current;i++)
    {
        //pthread_create(&threads.tid[i],NULL,threading_func,array.command_entity[i]);
        printf("%s %s %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time);
    }*/
    pthread_exit(NULL);
    free(array.command_entity);
    close(file);
    return 0;
}