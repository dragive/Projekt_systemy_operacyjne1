#include <stdio.h>
#include <unistd.h>
char* input_file;
char* output_file;


int parse_arguments(int argc, char *argv[]);

int input_file_open_to_read();

int output_file_open_to_write();

char* get_line_from_file(int file_link);

int check_line_format(char* input_line);

char ** split_command_line(char* input_line);

int get_local_time();

int convert_data_format_from_file();

void sort_input_lines(char**);

int compare_two_lines(char* first_line, char* second_line);

int main(int argc, char *argv[]){
    

}