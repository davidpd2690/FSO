#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define PBUFSIZE 64         //intital size for parsing buffer
#define PDELIM " \n\r\a\t"  //delimiter characters for parsing 

int main(int argc, char const *argv[])
{
    shellLoop();

    return EXIT_SUCCESS;
}

void shellLoop(void)
{
    char *line;
    char **args;
    int status;

    while (status)
    {
        printf("> ");
        line = readLine();
        args = parseLine(line);
        status = runShell(args);

        free(line);
        free(args);
    }

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
                printf("memory allocation failure \n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, PDELIM);
    }

    tokens[position] = NULL;
    return tokens;

}

int launchShell(char **args)
{
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if(pid1 == 0)   //child process
    {
        if (execvp(args[0], args) == -1)
        {
            perror("shell");
        }
        exit(EXIT_FAILURE);
    } 
    
    else if(pid1<0)   //error with fork()
    {
        perror("shell");
    }

    else //parent process
    {
        while(!WIFEXITED(status) && !WIFSIGNALED(status))
        {
            pid2 = waitpid(pid1, status, WUNTRACED);
        }
    }

    return 1;
}




