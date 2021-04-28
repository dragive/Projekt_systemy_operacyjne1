#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "singleLine.h"
#include "file.h"


/** @brief Get the new character from file and if reach end of file than change status.
 *
 * @param file File which character will be read from
 * @return char Character read from file
 * @author KF
 */
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

/** @brief Use it to read line from file.
 * @param file_link File which line will be read from
 * @param status Using to check status of reaching the end of file
 * @return Function returns singleLine struct object with read line
 * @author KF
 */
singleLine* get_line_from_file(int file_link,int* status){
    singleLine* sl = (singleLine*) malloc(sizeof(singleLine));
    sl->value=NULL;
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




/*@assgined to Kacper*/
//int check_line_format(char* input_line);

/** \brief Function splits string to array of strings that representing particular objects
 *
 * \param input_line line that will be converted to array of strings
 * \return array of strings
 */
char ** split(char* input_line, int number_of_words, char separator)
{
    int i=0, length=0, word=0;
    char** str_tab = (char**)malloc(number_of_words*sizeof(char*));
    char* temp_str;
    for(i=0; i<number_of_words;i++)
    {
        str_tab[i] = (char*)malloc(strlen(input_line)*sizeof(char));
    }

    i=0;

    while(input_line[i]!='\0')
    {
        if(input_line[i]==separator)
        {
            str_tab[word][length]='\0';
            word++;
            length=0;
        }
        else
        {
            str_tab[word][length]=input_line[i];
            length++;
        }
        i++;
    }
    str_tab[word][length]='\0';
    return str_tab;
}



void move_kasiu_stringi_dla_krzysia_off(char * str, int shift)
{
    if(shift>0)
    {
        for(int i =0;i<=strlen(str)-shift;i++){
            str[i]=str[i+shift];		
        }
    }
}


char** split_command_line(const char* str)
{
    int i;
    char** tab = (char**)malloc(4*sizeof(char*));
    tab[0] = (char*)malloc(3*sizeof(char));
    tab[1] = (char*)malloc(3*sizeof(char));
    tab[2] = (char*)malloc((strlen(str)-7)*sizeof(char));
    tab[3] = (char*)malloc(2*sizeof(char));
    tab[0][0]=str[0];
    tab[0][1]=str[1];
    tab[1][0]=str[3];
    tab[1][1]=str[4];
    tab[0][2]='\0';
    tab[1][2]='\0';
    tab[3][0]=str[strlen(str)-1];
    tab[3][1]='\0';
    for(i=6;i<strlen(str)-2;i++)
    {
        tab[2][i-6]=str[i];
    }
    tab[2][strlen(str)-2-6]='\0';
    return tab;
}


/**
 * @brief Function used to open input file for reading
 * @return int Value returned is file descriptor. If error occurs, return value -1.
 * @author Krzysztof Funkowski
 */
int open_read_file(const char* file_str)
{
    int file;
    if((file = open(file_str, O_RDONLY))<0) return -1;

    return file;
}





















