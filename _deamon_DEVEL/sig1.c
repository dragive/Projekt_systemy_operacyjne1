#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<signal.h>
int main(int *argc,char**argv){
	kill(atoi(argv[1]),SIGUSR1);
}//https://mylinuxthoughts.blogspot.com/2013/09/processes-daemons-and-signals.html
