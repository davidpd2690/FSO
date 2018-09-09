#define _GNU_SOURCE 
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int leibniz(void *arg);

long double result = 0.0;
long niterations;
long long start_ts;
long long stop_ts;
int elapsed_time;

struct timeval ts;

int main(int argc, char const *argv[])
{

    void *stack;
    stack = malloc(1024 * 1024);
    if(!stack) 
    {
        printf("memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    int pid = clone(*leibniz, stack + (1024 + 1024), SIGCHLD, 0);
    if ( pid < 0 ) 
    {
        printf("error creating the child process.\n");
        exit(EXIT_FAILURE);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("result: %Lf\n", result/4);
    printf("time: %d microseconds\n", elapsed_time);

    return 0;
}


int leibniz(void *arg)
{
    long double lresult = 0.0;
    long i;// = atoi(arg);

        for(i=0; i<niterations; i++)
    {

        lresult += pow(-1, i)/(2*i+1);

    }

    result += lresult * 2;

}