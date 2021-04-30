/**
 * @file start_lib.c
 * @author Maciej Fender
 * @brief start function used on start of the program
 * @version 1
 * @date 2021-03-25
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "start_lib.h"



/** \brief Function to run program as daemon
 *
 * \return new process id; pid of the created daemon
 * \author MF
 */
int daemon2()
{
    int debug= 0;
    pid_t process_id = 0;
    pid_t sid = 0;
    /// Create child process
    process_id = fork();
    /// Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
    /// Return failure in exit status
        exit(1);
    }
    /// PARENT PROCESS. Need to kill it.
    if (process_id > 0)
    {
        if(debug)printf("process_id of child process %d \n", process_id);
    /// return success in exit status
        exit(0);
    }
    ///unmask the file mode
    umask(0);
    ///set new session
    sid = setsid();
    if(sid < 0)
    {
    /// Return failure
        exit(1);
    }

    /// Close stdin. stdout and stderr

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
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
 * @brief Function gets arguments from start of the program, validate and assigns to propriete  global variable.
 *
 * @param argc Number of arguments
 * @param argv The array of arguments.
 * @return int Indicator whether process of parsing arguments gone well. When it's ok then 0, else something gone wrong.
 * @author MF
 */
int parse_arguments(int argc, char **argv){
    /// if there's not enough arguments
    if( argc < 3 ) {
        return 3-argc;
    }
    ///if there's too many arguments
    else if (argc > 3){
        return argc;
    }
    ///it's ok
    else{
        /// copying args to variables
        input_file=(char*)malloc((strlen(argv[1])+1)*sizeof(char));
        output_file=(char*)malloc((strlen(argv[2])+1)*sizeof(char));
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
