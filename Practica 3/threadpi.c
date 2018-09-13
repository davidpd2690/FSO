#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define NTHREADS 4

void *leibniz(void *thread);

long double result = 0.0;
long niterations;
long long start_ts;
long long stop_ts;
int elapsed_time;

struct timeval ts;

int main(int argc, char const *argv[])
{
    int i;
    pthread_t tids[NTHREADS];
    int parr[NTHREADS];

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    for(i=0;i<NTHREADS;i++)
    {
        parr[i] = i;
        pthread_create(&tids[i], NULL, leibniz, (void *) &parr[i]);
    }
    
    
    for(i=0;i<NTHREADS;i++)
    {
        pthread_join(tids[i], NULL);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("time: %d microseconds\n", elapsed_time);

    return 0;
}


void *leibniz(void *args)
{
    long double lresult = 0.0;
    long i;
    int nthread = *((int *) args);

        for(i=0; i<niterations; i++)
    {

        lresult += pow(-1, i)/(2*i+1);

    }

    printf("result: %Lf\n", lresult);

}