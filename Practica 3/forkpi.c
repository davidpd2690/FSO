#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>

int leibniz(int segment_id);

long double *result;
long niterations;
long long start_ts;
long long stop_ts;
int elapsed_time;

struct timeval ts;

int main(int argc, char const *argv[])
{
    int i, status;
    pid_t pid;

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    int segment_id = shmget(IPC_PRIVATE, sizeof(result), S_IRUSR | S_IWUSR);
    result = shmat(segment_id, NULL, 0);

        pid = fork();
        if(pid == 0)
        {
            leibniz(segment_id);
            exit(0);
        }

        else if(pid < 0)
        {
            printf("error forking\n");
        }


    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("time: %d microseconds\n", elapsed_time);

    return 0;
}

int leibniz(int segment_id)
{
    long double lresult = 0.0;
    long i;// = atoi(arg);

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    for(i=0; i<niterations; i++)
    {

        lresult += pow(-1, i)/(2*i+1);

    }

    printf("result: %Lf\n", lresult);
}