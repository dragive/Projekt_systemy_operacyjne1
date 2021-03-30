#include <unistd.h>
#include "singleLine.h"


/** @brief Function used to open input file for reading
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @author MF
 */
int open_to_read_file(const char *  file_name){

    int status = open(file_name,"r");
    if ( status == 0 ) perror("File open to read error");
    return status;

}
/** @brief Function used to open output file for appending
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @see open_to_read_input_file()
 * @author MF
 */
int open_to_append_file(const char *  file_name){

    int status = open(file_name,"a+");
    if ( status == 0 ) perror("File open to write error");
    return status;

}
/** @brief Use it to read line from file
 *
 * @param file_link File which line will be read from
 * @return Function returns singleLine struct object with read line
 * @author KF
 */

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

/** @brief Get the new character from file
 *
 * @param file File which character will be read from
 * @return char Character read from file
 * @authot KF
 */
char get_new_character_from_file(int file){
    char* buffer = (char*)malloc(sizeof(char));
    ssize_t c;
    if(c = read(file,buffer,1)>0)
    {
        return buffer[0];
    }
    return 'x';
}

/** \brief Read line from file
 *
 * \param Line struct to which characters will be written
 * \param File which characters are read from
 * \return Array of characters read from file
 * \author MF
 */

char* get_line_from_file(singleLine *line,int file){
    if(line == NULL){
        line = (singleLine*) malloc(sizeof(singleLine));
    }
    char read='\0';
    while(1){

        read = get_new_character_from_file(file);

        if(read == '\r'){
            break;
        }

    }

    return singleLine.pointer_to_value;

}
/*@assgined to Kacper*/
int check_line_format(char* input_line);

/*Krzysiek i struct*/
char ** split_command_line(char* input_line);

int convert_singleLine_to_struct();

void sort_input_lines(char**);


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
int compare_two_lines_based_on_time(                       );





















