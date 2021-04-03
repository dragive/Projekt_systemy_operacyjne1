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



/** @brief Function used to open input file for reading
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @author MF
 */
/*int open_to_read_file(const char *  file_name){

    int status = open(file_name,"r");
    if ( status == 0 ) perror("File open to read error");
    return status;

}*/
/** @brief Function used to open output file for appending
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @see open_to_read_input_file()
 * @author MF
 */
/*int open_to_append_file(const char *  file_name){

    int status = open(file_name,"a+");
    if ( status == 0 ) perror("File open to write error");
    return status;

}*/

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
            //str_tab[word][length-1]='\0';
            /*temp_str=str_tab[word];
            memmove(temp_str,str_tab[word]+1,strlen(str_tab[word]));
            str_tab[word]=temp_str;*/
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
    //str_tab[word][length-1]='\0';
    /*temp_str=str_tab[word];
    memmove(temp_str,str_tab[word]+1,strlen(str_tab[word]));
    str_tab[word]=temp_str;*/
    return str_tab;
}

//DO POPRAWY
char ** split_command_line(char* input_line)
{
    int i=0, length=0, word=0, words_count=4;
    char** str_tab = (char**)malloc(words_count*sizeof(char*));
    char* temp_str;
    for(i=0; i<words_count;i++)
    {
        str_tab[i] = (char*)malloc(strlen(input_line)*sizeof(char));
    }
    /*memcpy(str_tab[0],&input_line[0],2);
    str_tab[0][3]='\0';
    memcpy(str_tab[1],&input_line[3],2);
    str_tab[1][3]='\0';
    memcpy(str_tab[2],&input_line[6],strlen(input_line)-5);
    str_tab[2][3]='\0';
    memcpy(str_tab[3],&input_line[strlen(input_line)-1],1);
    str_tab[3][2]='\0';*/
    return str_tab;
}


//int convert_singleLine_to_struct();

//void sort_input_lines(char**);


/**
 * @brief Function used to open input file for reading
 * @return int Value returned is file descriptor. If error occurs, return value -1.
 * @author Krzysztof Funkowski
 */
int open_read_file(const char* file_str)
{
    int file;
    if((file = open(file_str, O_RDONLY))==-1) return -1;

    return file;
}



/*
params are structs containing parsed command line
*/
//int compare_two_lines_based_on_time(                       );





















