#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // grab command line arguments
    printf("argc: %d\n", argc);
    printf("argv0: %s\n", argv[0]);
    printf("argv1: %s\n", argv[1]);

    // setting environment variables
    // let's say I want to set MY_NAME to my name
    // example using putenv
    int result = putenv("MY_NAME=eric");
    if (result == -1)
    {
        printf("Error checking putenv");
        return -1;
    }

    char *env_results = getenv("MY_NAME");
    printf("MY_NAME: %s\n", env_results);

    // example using setenv
    // int setenv(const char *name, const char *value, int overwrite);
    int setenv_results = putenv("MY_NAME2=eric2");
    char *env_results2 = getenv("MY_NAME2");
    printf("MY_NAME2: %s\n", env_results2);

    // get process id
    char buff[10] = {0};
    int pid = getpid();
    sprintf(buff, "%d", pid);
    printf("my process id is: %s\n", buff);

    return 0;
}