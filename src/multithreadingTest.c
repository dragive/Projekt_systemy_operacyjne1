#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

typedef struct singleLine
{
    char * value;       /** Pointer to table of chars read from file */
    int size_max;       /** Max size which can be currently stored */
    int size_current;   /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
} singleLine;

void* threading_func(void* vargp)
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


}

int main(int argc, char** argv)
{
    int i,pid,child_pid;
    char str[12]="abc";
    char *args[] = {"echo","3",NULL};

    pthread_t tid[3];
    singleLine sl[3];
    sl[0].size_max=5;
    sl[1].size_max=1;
    sl[2].size_max=0;
    for(i=0;i<3;i++)
    {
        pthread_create(&tid[i],NULL,threading_func,&sl[i]);
    }
    pthread_exit(NULL);
}
