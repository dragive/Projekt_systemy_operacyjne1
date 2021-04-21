#include <time.h>
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
#include <stdarg.h>
int daemon2()
{
    int debug= 1;
    pid_t process_id = 0;
    pid_t sid = 0;
// Create child process
    process_id = fork();
// Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
// Return failure in exit status
        exit(1);
    }
// PARENT PROCESS. Need to kill it.
    if (process_id > 0)
    {
        if(debug)printf("process_id of child process %d \n", process_id);
// return success in exit status
        exit(0);
    }
//unmask the file mode
    umask(0);
//set new session
    sid = setsid();
    if(sid < 0)
    {
// Return failure
        exit(1);
    }
// Change the current working directory to root.
    chdir("/");
// Close stdin. stdout and stderr
    close(STDIN_FILENO);
    //close(STDOUT_FILENO);
    close(STDERR_FILENO);

    return process_id;
}


/**
 * @brief Global variable storing name of input file
 */
char* input_file;

/**
 * @brief Global variable storing name of output file
 */
char* output_file;

/**
 * @brief Function gets arguments from start of the program, validate and assigns to propriete global variable.
 *
 * @param argc Number of arguments
 * @param argv The array of arguments.
 * @return int Indicator whether process of parsing arugments gone well. When it's ok then 0, else something gone wrong.
 * @author MF
 */
int parse_arguments(int argc, char *argv[]){
    if( argc < 3 ) {
        return 3-argc;
    }
    else if (argc >3){
        return argc;
    }
    else{
        strcpy(input_file,argv[1]);
        strcpy(output_file,argv[2]);
    }
    return 0;

}

/** \brief Getter of input_file
 * \author MF
 */


char* get_input_file_name(){
    return input_file;
}


/** \brief Getter of output_file
 * \author MF
 */

char* get_output_file_name(){
    return output_file;
}
/*
int get_system_time_hour(){
    struct tm localTime = localtime(time(null));  // Get system time using system time zone
    return localTime.tm_hour;
}
int get_system_time_minute(){
    struct tm localTime = localtime(time(null));  // Get system time using system time zone
    return localTime.tm_min;
}
*/
/** \brief function to log actions
 *
 * \param message Message to be writen to log system file
 *
 */

void log(char* message){
        /// IMPORTANT!!!!!!!!!        PUT IN IN THE FIRST LIEN OF MAIN openlog("programname", 0, LOG_USER);
        syslog(LOG_INFO, "%s", message);
}

