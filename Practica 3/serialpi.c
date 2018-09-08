#include <stdio.h>
#include <math.h>
#include <sys/time.h>

long long start_ts;
long long stop_ts;
long double result;
int i, n, elapsed_time;

struct timeval ts;

int main(int argc, char const *argv[])
{
    
    printf("Number of iterations: \n");
    scanf("%d", &n);

    gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
    for(i=0; i<n; i++)
    {

        result += pow(-1, i)/(2*i+1);

    }

    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;

    elapsed_time = (int)(stop_ts - start_ts);

    printf("result: %Lf\n", result);
    printf("time: %d microseconds\n", elapsed_time);

    return 0;
}

