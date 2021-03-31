#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "file.h"
#include "singleLine.h"
#include "commandEntity.h"
#include "dayTime.h"

/*void* threading_func(void* vargp)
{
    int i,pid,child_pid,time;
    singleLine* sl = (singleLine*)vargp;
    char ch[1];
    sprintf(ch,"%d",sl->size_max);
    char *args[] = {"echo","3",NULL};
    pid = fork();
        if(pid == 0)
        {

            child_pid = fork();
            if(child_pid == 0)
            {
                execlp("sleep","sleep",ch, NULL);
                exit(0);
            }
            else
            {
                //printf("CHILD CHILD END\n");
                wait(NULL);
            }
            //printf("CHILD END\n");
            execvp("echo",args);
            exit(0);
        }
        else
        {
            wait(NULL);
            //printf("PARENT END\n");
        }


}*/

int main(int argc, char** argv)
{
    int file,status=0;
    char* file_str = "testowy.txt";
    if((file = open_read_file(file_str))==-1) return -1;
    singleLine* sl = NULL;
    //sl = get_line_from_file(file,&status);
    //if(sl != NULL) printf("%s\n",sl->value);
    while(status==0)
    {
        sl = get_line_from_file(file,&status);
        if(sl != NULL) printf("%s\n",sl->value);
        free(sl);
    }
    close(file);
    return 0;
}
