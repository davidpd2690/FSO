#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define NPROCS 6

int main(int argc, char const *argv[])
{
    pid_t pidt;
    
    int i;
    int pid,status;
    int killproc;

    int *shutdown = 0;
    int *sdptr;
    int *pids;
    int *pidsptr;

    sdptr = (int*) malloc(status * sizeof(int));
    pidsptr = (int*) malloc(pid * sizeof(int));

    shutdown = sdptr;
    pids = pidsptr;

    for(i=0;i<NPROCS;i++)
    {
        pid = fork();

        if(pid == 0)
        {
            execlp("/usr/bin/xterm", "/usr/bin/xterm", "-e", "./getty.exe", NULL);
        }

        else pids[i] = pid;

    }

    while(!*shutdown)
    {
        pidt = wait(&status);

        for(i = 0; i < NPROCS; i++)
        {
            killproc = kill(pids[i], 0);
            if(killproc < 0)
            {
                pid = fork();
            }

            if(pid == 0)
            {
                execlp("/usr/bin/xterm", "/usr/bin/xterm", "-e", "./getty.exe", NULL);
            }
        }
    }
    return 0;
}


