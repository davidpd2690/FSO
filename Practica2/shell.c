#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PBUFSIZE 64         
#define PDELIM " \n"  


int executeCmd(char **args);

char *readLine(void);
char **parseLine(char *line);

void shellLoop(void);

int main(int argc, char const *argv[])
{
    char *line;
    char **args;
    int status;

    while (&status)
    {
        printf("sh > ");
        line = readLine();
        args = parseLine(line);
        status = executeCmd(args);
    }

    return EXIT_SUCCESS;
}

char *readLine(void)
{
    char *line = NULL;
    ssize_t bufferSize = 0;
    getline(&line, &bufferSize, stdin);
    return line;
}

char **parseLine(char *line)
{
    int bufferSize = PBUFSIZE, position = 0;
    char **tokens = malloc(bufferSize * sizeof(char*));
    char *token;
    token = strtok(line, PDELIM);

    if(!tokens)
    {
        printf("memory allocation error \n");
        exit(EXIT_FAILURE);
    }

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= bufferSize)
        {
            bufferSize += PBUFSIZE;
            tokens = realloc(tokens, bufferSize * sizeof(char*));
            if(!tokens)
            {
                printf("memory re-allocation failure \n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, PDELIM);
    }

    tokens[position] = NULL;
    return tokens;

}

int executeCmd(char **args)
{
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if(pid1 == 0)   //child process
    {
        
        if(strcmp(args[0], "exit") == 0)
        {
            kill(getpid(), SIGQUIT);
        }
        
        if (execvp(args[0], args) == -1)
        {
            printf("error executing command/command not found\n");
        }

    } 
    
    else if(pid1<0)   //error with fork()
    {
        printf("error forking\n");
    }

    else //parent process
    {
        while(!&status)
        {
            pid2 = waitpid(pid1, &status, WUNTRACED);
        }

    }

    return 1;
}







