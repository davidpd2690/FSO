#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define NPROCS 6

int main(int argc, char const *argv[])
{
    pid_t pidt;
    
    int i;
    int pid, pidArr, sd;
    int endProcess;

    int *shutdown = 0;
    int *sdptr;
    int *pids;
    int *pidsptr;

    sdptr = (int*) malloc(sd * sizeof(int));
    pidsptr = (int*) malloc(pidArr * sizeof(int));

    shutdown = sdptr;
    pids = pidsptr;

    for(i=0;i<NPROCS;i++)
    {
        pid = fork();

        if(pid == 0)
        {
            execl("/usr/bin/xterm", "/usr/bin/xterm", "-e", "./getty.exe", NULL);
        }

        else pids[i] = pid;

    }

    while(!*shutdown)
    {
        for(i = 0; i < NPROCS; i++)
        {
            endProcess = kill(pids[i], 0);
            if(endProcess < 0)
            {
                pid = fork();
            }

            if(pid == 0)
            {
                execl("/usr/bin/xterm", "/usr/bin/xterm", "-e", "./getty.exe", NULL);
            }
        }
    }
    return 0;
}


