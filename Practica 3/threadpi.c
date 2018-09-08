#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

void *leibniz(void *thread);

long double result = 0.0;
long niterations;
long long start_ts;
long long stop_ts;
int elapsed_time;

struct timeval ts;

int main(int argc, char const *argv[])
{
    pthread_t tid1;
    pthread_t tid2;

    int treturn1, treturn2;
    long i;

    printf("Number of iterations: \n");
    scanf("%ld", &niterations);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    treturn1 = pthread_create(&tid1, NULL, leibniz,(void *)i);
    treturn2 = pthread_create(&tid2, NULL, leibniz,(void *)i);

    if(treturn1)
    {
        printf("error creating thread1, error code %d\n", treturn1);
    }

    if(treturn2)
    {
        printf("error creating thread2, error code %d\n", treturn2);
    }


    treturn1 = pthread_join(tid1, NULL);
    treturn2 = pthread_join(tid2, NULL);
         
    if(treturn1)
    {
        printf("error joining thread1, error code %d\n", treturn1);
    }

    if(treturn2)
    {
        printf("error joining thread2, error code %d\n", treturn2);
    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("result: %Lf\n", result/4);
    printf("time: %d microseconds\n", elapsed_time);

    return 0;
}


void *leibniz(void *arg)
{
    long double lresult = 0.0;
    long i = (long)arg;

        for(i=0; i<niterations; i++)
    {

        lresult += pow(-1, i)/(2*i+1);

    }

    result += lresult * 2;

}