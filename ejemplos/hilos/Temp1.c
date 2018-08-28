#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>



void *Texto1 (void *Text1);


int main(int argc, char const *argv[])
{
    /* code */

    pthread_t ptid1, ptid2;

    char *text1 ="Hola";
    char *text2 ="Mundo";

    pthread_create(&ptid1, NULL, Texto1, (void *)text1);
    pthread_create(&ptid2, NULL, Texto1, (void *)text2);

    pthread_join(ptid1, NULL);
    pthread_join(ptid2, NULL);

    printf("finalizacion de hilos");

    return 0;
}

void *Texto1(void *Text1)
{
    char *tex="";
    int i;
    tex = (char *) Text1;

    for(i=0; i<strlen(tex); i++)
    {
        printf("%c ", tex[i]);
        fflush(stdout);
        usleep(1000000);
    }

    return NULL;
}

