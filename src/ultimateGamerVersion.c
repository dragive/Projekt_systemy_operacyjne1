#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include "start_lib.h"

int main()
{
    openlog("output", 0, LOG_USER);
    daemon2();
    syslog(LOG_NOTICE, "First daemon started.");
    syslog(LOG_NOTICE, "First daemon terminated.");
    closelog();

    return EXIT_SUCCESS;
}