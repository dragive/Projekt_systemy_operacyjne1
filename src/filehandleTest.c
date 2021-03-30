#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int open_read_file(const char* file_str);

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

char get_new_character_from_file(int file){
    char* buffer = (char*)malloc(sizeof(char));
    ssize_t c;
    if(c = read(file,buffer,1)>0)
    {
        return buffer[0];
    }
    return 'x';
}



singleLine* get_line_from_file(int file_link){
    singleLine* sl = (singleLine*) malloc(sizeof(singleLine));
    char read;
    while((read = get_new_character_from_file(file_link))!='\n')
    {
        add_char_to_singleLine(sl,read);
    }
    /*while(1){
        read = get_new_character_from_file(file_link);
        printf("brr");
        if(read=='\r'){get_new_character_from_file(file_link);break;}
        else if (read =='\0')break;
        else{
            add_char_to_singleLine(sl,read);
        }
    }*/
    return sl;
}

int open_read_file(const char* file_str)
{
    int file;
    if((file = open(file_str, O_RDONLY))==-1) return -1;

    return file;
}

int main(int argc, char** argv)
{
    /*int i,pid,child_pid;
    char str[12];
    for(int i=0;i<5;i++)
    {
        sprintf(str,"%d",i);
        pid = fork();
        if(pid == 0)
        {
            child_pid = fork();
            if(child_pid == 0)
            {
                execlp("sleep","sleep","3", NULL);
                exit(0);
            }
            else
            {
                printf("CHILD CHILD END\n");
                wait(NULL);
            }
            printf("CHILD END\n");
            execlp("echo","echo",str,NULL);
            exit(0);
        }
        else
        {
            wait(NULL);
            printf("PARENT END\n");
        }
    }*/
    int file;
    char* file_str = "testowy.txt";
    if((file = open_read_file(file_str))==-1) return -1;
    singleLine *sl = NULL;
    sl = get_line_from_file(file);
    if(sl != NULL) printf("%s",sl->value);
    close(file);
    return 0;
}
