/**
 * @file main.c
 * @author Maciej Fender
 * @brief Main file of the program
 * @version 0.1
 * @date 2021-03-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "singleLine.h"
#incldue "start_lib.h"

/** \brief Get the remaining time to execute the command
 *
 * \param command_line command entity needed to get it's time for calculations
 * \return remaining time from now to execute the command
 * \author Krzysztof Funkowski
 */
int remaining_time_to_execution(command_struct* command_line)
{
    int temp = command_line->time - get_time_in_sec();
    return (temp>=0)?temp:-1;
}

char* get_pipe_parameter(char* str){

    if(!strcmp(str,"0"))return "";
    else if( !strcmp(str,"1") ) return "1>&2";
    else if(!strcmp(str,"2")) return "| tee /dev/stderr";

}
/*

CHANGECHANGECHANGECHANGECHANGECHANGECHANGECHANGECHANGECHANGECHANGECHANGE


*/
void threading_func(command_struct* to_execute){
    sleep(to_execute.time);
    char* cmd = malloc(sizeof(char)*strlen(to_execute.command)+5);
    strcpy(cmd,to_execute);

    strcat(cmd,get_pipe_parameter(to_execute.parameter));
    system(cmd);
}


int main(int argc, char *argv[]){




    openlog("MINI CRONE", 0, LOG_USER);



    int file,status=0,line_count=0,i;

    char** splitted_array;

    parse_arguments(argc,argv);
    char* file_str = get_input_file_name();


    pthread_t tid[6];
    if((file = open_read_file(file_str))==-1) return -1;

    command_array array;
    init_command_struct_array(&array,10);
    /** TO CHANGE BEGIN*/
    singleLine* sl = NULL;
    while(status==0)
    {
        sl = get_line_from_file(file,&status);
        if(sl != NULL)
        {
            splitted_array=split(sl->value,4,':');
            //printf("SIZE: %d\n",array.size_current);
            if(array.size_current==array.size_max) {array.command_entity=extend_command_line_array(&array,5);}
            array.command_entity[array.size_current++]=convert_command_to_struct(splitted_array);
        }
        free(sl);
    }

    for(i=0;i<array.size_current;i++)
    {
        pthread_create(&tid[i],NULL,threading_func,array.command_entity[i]);
        //printf("%s %s %d\n",array.command_entity[i]->command,array.command_entity[i]->parameter,array.command_entity[i]->time);
    }
    pthread_exit(NULL);
    /*for(i=0;i<array.size_max;i++)
    {
        free_command(array.command_entity[i]);
    }*/
    /** TO CHANGE END*/
    free(array.command_entity);
    close(file);
    return 0;

}
