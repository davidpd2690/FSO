#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define PBUFSIZE 64 

int credentialValidation(char *user, char*password);

int main(int argc, char const *argv[])
{
    int pid1, pid2;
    int status;
    int id = 0;
    int bufferSize = PBUFSIZE;

    int *pid1ptr, *pid2ptr;
    int *pids;
    int *shutdown;
    char *token;
    char *tokens = malloc(bufferSize * sizeof(char*));
    char *user = malloc(bufferSize * sizeof(char*));
    char *password = malloc(bufferSize * sizeof(char*));
    
    pid1ptr = (int*) malloc(pid1 * sizeof(int));
    pid2ptr = (int*) malloc(pid2 * sizeof(int));

    shutdown = pid1ptr;
    pids = pid2ptr;
    
    pid2 = fork();
    printf("pid2: %d\n", pid2);
    if(pid2 == 0)
    {
        int login = 0;
        while(1)
        {
            while(login == 0)
            {
                printf("User: \n");

                if(fgets(tokens, sizeof(tokens), stdin))
                {
                    if(sscanf(tokens, "%s", user) == 1);
                }

                printf("Password: \n");

                if(fgets(tokens, sizeof(tokens), stdin))
                {
                    if(sscanf(tokens, "%s", password) == 1);
                }

                if (credentialValidation(user,password) == 1)
                {   
                    printf("Login successful\n");
                    login = 1;
                }

                else 
                {
                    printf("login is incorrect, try again\n");
                    login = 0;
                }
            }   
        }
    }
    else if(pid2 > 0)
    {
        
        while (!*shutdown)
        {
            sleep(4);
        }
    }

    return 0;
}

int credentialValidation(char *user, char *password)
{
    FILE* fid;
    fpos_t position;
    int initP = 0;
    int bufferSize = PBUFSIZE;

    char *userInput = malloc(bufferSize * sizeof(char*));
    char *passwordInput = malloc(bufferSize * sizeof(char*));

    if((fid = fopen("passwd.txt", "rw+")) == NULL)
    {
        printf("error opening file\n");
        sleep(4);
        fclose(fid);
        return 0;
    }

    if(initP)
    {
        fsetpos(fid, &position);
    }

    while(!feof(fid))
    {
        if(fscanf(fid, "%s : %s", userInput, passwordInput))
        {
            if(strcmp(userInput, user) == 0 && strcmp(passwordInput, password) == 0)
            {
                return 1;
            }

        }

        fgetpos(fid,&position);
        initP = 1;
    }

    return 0;
}
