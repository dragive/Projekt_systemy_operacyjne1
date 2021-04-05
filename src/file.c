#include <unistd.h>
#include "singleLine.h"


/**
 * @brief Function used to open input file for reading
 * Function where there would be error will print to stderr details, or will open file
 * @return int Value returned is 0 if error occured, else number representing pinter to file
 * @author MF
 */
int open_to_read_file(const char *  file_name){

    int status = open(file_name,"r");
    if ( status == 0 ) perror("File open to read error");
    return status;

}
/**
 * @brief Function used to open output file for appending
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
/*
Krzysiek jeżeli masz czas to też proszę zobacz tą funkcję

*/
char* get_line_from_file(int file_link){
        /**
         * propably this function's to be implementd as readint 1 B from file and checking whether it is end of line or not
         * it is signed as \r\n so checking \r char will be enough
         * PLS USE single line struct to automaticly check buffor and lenght of line
         */
}

/**
 * @brief Get the new character from file
 *
 * @param file File which character will be read from
 * @return char Character read from file
 */
char get_new_character_from_file(int file){

    return read(file,1,sizeof(char));

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
int check_line_format(char* input_line){
    size_t lenght = strlen(input_line);
    char hours, minutes, info;
    hours = input_line[0]+input_line[1];
    info = input_line[lenght];
    int hours_temp = charToInt(hours);
    int test=0;
    int info_temp = atoi(info);
    if(hours_temp>=0 && hours_temp<=23)
    {
        minutes = input_line[3]+input_line[4];
        int minutes_temp = charToInt(minutes);
        if(minutes_temp>=0 && minutes_temp<=59)
        {
            for(int i=6;i<=lenght-1;i++)
            {
                if(input_line[i]!="")
                {
                    test++;
                }
                if(test>0)
                {
                    if(info_temp>=0 && info_temp<=2)
                    {
                        printf("Jest git");
                    }
                    else
                    {
                        return 4;
                    }
                }
                else
                {
                    return 3;
                }
            }
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 1;
    }
}

/*Krzysiek i struct*/
char ** split_command_line(char* input_line);

int convert_singleLine_to_struct();

void sort_input_lines(char**);


/*
params are structs containing parsed command line
*/
int compare_two_lines_based_on_time(                       );





















