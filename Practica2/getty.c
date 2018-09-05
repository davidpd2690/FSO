#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PBUFSIZE 64 
#define FILENAME "passwd.txt"

int login(char *user, char*password);

int main(int argc, char const *argv[])
{
    pid_t pid1, pid2;

    int status;
    int bufferSize = PBUFSIZE;

    int *pid1ptr, *pid2ptr;
    int *shutdown;

    char *input;

    char *user = malloc(bufferSize * sizeof(char*));
    char *password = malloc(bufferSize * sizeof(char*));
    
    pid1ptr = (int*) malloc(pid1 * sizeof(int));
    pid2ptr = (int*) malloc(pid2 * sizeof(int));

    shutdown = pid1ptr;

    
    pid2 = fork();
    if (pid2 < 0)
    {
        printf("error forking\n");
        exit(0);
    }

    if(pid2 == 0)
    {
        int flag = 0;

        while(flag == 0)
        {
            printf("User: \n");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%s", user);

            printf("Password: \n");
            fgets(input, sizeof(input), stdin);
            sscanf(input, "%s", password);
                

            if (login(user,password) == 1)
            {   
                flag = 1;
            }

            else 
            {
                printf("login is incorrect, try again\n");
                flag = 0;
            }
        } 

        pid1 = fork();

        if(pid1 == 0)
        {
            execlp("./shell.exe", "./shell.exe", (char*)NULL);
        }

        else wait(&status);

        flag = 0;

    }

    else if(pid2 > 0)
    {
        while (!*shutdown)
        {
            wait(&status);
        }
    }

    return 0;
}



int login(char *user, char *password)
{
    int bufferSize = PBUFSIZE;

    char *userInput = malloc(bufferSize * sizeof(char*));
    char *passwordInput = malloc(bufferSize * sizeof(char*));

    FILE *file;

    file = fopen(FILENAME, "rw+");

    if(file == NULL)
    {
        printf("error opening file\n");
        sleep(4);
        fclose(file);
        return 0;
    }

    while(!feof(file))
    {
        fscanf(file, "%s : %s", userInput, passwordInput);
        
        if(strcmp(userInput, user) == 0 && strcmp(passwordInput, password) == 0)
        {
            return 1;
        }

    }

    return 0;
}


