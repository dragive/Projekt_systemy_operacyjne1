
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct singleLine
{
    char * value;       /** Pointer to table of chars read from file */
    int size_max;       /** Max size which can be currently stored */
    int size_current;   /** Current number of characters, e.g. 0 if there's nothing and 1 if there's 1 character*/
} singleLine;

void extend_buffor_singleLine(singleLine* sl){
    char * temp = (char* ) malloc(sizeof(char)*sl->size_max+10);
    for(int i = 0;i<sl->size_max;i++){
        temp[i] = sl->value[i];
    }
    free(sl->value);
    sl->value = temp;
    sl->size_max += 10;
}

void add_char_to_singleLine(singleLine * sl,char c){
    if(sl == NULL){
        sl = (singleLine*) malloc(sizeof(singleLine));
    }
    if(sl->value == NULL){
        sl->size_max = 10;
        sl->size_current = 0;
        sl->value = (char*) malloc(sizeof(char)*sl->size_max);
        sl->value[sl->size_current]='\0';
    }
    if(sl->size_current ==  sl->size_max-1){
        extend_buffor_singleLine(sl);
    }
    sl->value[sl->size_current++] = c;
    sl->value[sl->size_current] = '\0';
}

char get_new_character_from_file(int file,int* status){
    char* buffer = (char*)malloc(sizeof(char));
    ssize_t c;
    if(c = read(file,buffer,1)>0)
    {
        return buffer[0];
    }
    *status=1;
    return 'x';
}

singleLine* get_line_from_file(int file_link,int* status){
    singleLine* sl = (singleLine*) malloc(sizeof(singleLine));
    char read;
    while((read = get_new_character_from_file(file_link,status))!='\n')
    {
        //printf("%c",read);
        if(*status==1)
        {
            free(sl);
            sl=NULL;
            break;
        }
        add_char_to_singleLine(sl,read);
    }
    return sl;
}

int open_read_file(const char* file_str)
{
    int file;
    if((file = open(file_str, O_RDONLY))==-1) return -1;

    return file;
}

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
