#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int daemon2()
{
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
        printf("process_id of child process %d \n", process_id);
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
void helloworld(int no){
    printf("no");
}
int main(){
    ///ustawienie by wykrywany był signal SIGUSR1, może być wywołany przy pomocy programu s1.c
    signal(SIGUSR1,helloworld);
    /// program zamieniany jest w demona a jego PID zwracany jest i wypisaywany
    printf("%d",daemon2());

    ///Testowe
    for(int i =0;i<20;i++){
            ///    ^^ 20*1 sekund i każda sekunda to wypisanie również jej na konsole
        sleep(1);
        printf("%d",i);
        fflush(stdout); /// potrzeba ta linijka bo bufor jest slushowany po zakonczeniu demona dopiero
    }
    return 0;
}//https://mylinuxthoughts.blogspot.com/2013/09/processes-daemons-and-signals.html
