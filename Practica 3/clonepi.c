#define _GNU_SOURCE 
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


#define STACKSIZE 4096
#define NTHREADS 4

int leibniz(void *args);

long niterations;
long long start_ts;
long long stop_ts;
int elapsed_time;

struct timeval ts;

void *child_stack;

int leibniz(void *args)
{
    long double lresult = 0.0;
    long i;

    printf("executing function...\n");
        for(i=0; i<niterations; i++)
    {

        lresult += pow(-1, i)/(2*i+1);

    }

    printf("result: %Lf\n", lresult);


    printf("ending function...\n");
    //return 0;
}

int main(int argc, char const *argv[])
{

    printf("process id: %u\n", getpid());
    child_stack = malloc(STACKSIZE * 32);
    int i;
    int arr[NTHREADS], threadids[NTHREADS];

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    for(i=0;i<NTHREADS;i++)
    {
        arr[i] = i;
        printf("creating new thread...\n");
        threadids[i] = clone(&leibniz, (char *)child_stack + STACKSIZE * 16, SIGCHLD|CLONE_SIGHAND|CLONE_VM, (void *)&arr[i]);
        printf("thread id: %d\n", threadids[i]);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("time: %d microseconds\n", elapsed_time);

    free(child_stack);
    return 0;
}
