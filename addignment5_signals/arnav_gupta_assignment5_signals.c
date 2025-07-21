#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define SYNC_SIG SIGUSR1 /* Synchronization signal */
pid_t childPid = -1;

char *currTime(const char *format)
{
    static char buf[256];
    time_t t;
    size_t len;
    struct tm *tm;

    t = time(NULL);
    tm = localtime(&t);
    if (tm == NULL)
        return NULL;

    len = strftime(buf, sizeof(buf), (format != NULL) ? format : "%c", tm);
    return (len == 0) ? NULL : buf;
}

/*
Signal Handlers:
Use the sigaction() function to set up signal handlers (signal_handler_1() for SIGUSR1 and signal_handler_2() for SIGUSR2).
signal_handler_1() should print: "Child received SIGUSR1!\n".
signal_handler_2() should print: "Parent received SIGUSR2!\n".
*/

void signal_handler_1(int signal) {
    if (getpid() == childPid) {
        printf("Child received SIGUSR1!\n");
    } else {
        printf("Parent received SIGUSR1!\n");
    }
}

// Handler for SIGUSR2 (used by parent)
void signal_handler_2(int signal) {
    printf("Parent received SIGUSR2!\n");
}

int main(int argc, char *argv[])
{
    sigset_t blockMask, origMask, emptyMask;
    struct sigaction sa1, sa2;
    // parent process execution flow
    // Once initialized, the parent should print: "Parent started...\n".
    printf("Parent started...\n");
    //Sleep for 3 seconds.
    sleep(3);
    // Print: "Parent about to signal child...\n".
    printf("Parent about to signal child...\n");

    //Signal Mask:
    // Before calling fork(), modify the parent process's signal mask to block SIGUSR1 and SIGUSR2.
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGUSR1); 
    sigaddset(&blockMask, SIGUSR2);    
    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

        // Set up signal handler for SIGUSR1
    sa1.sa_handler = signal_handler_1;
    sigemptyset(&sa1.sa_mask);
    sa1.sa_flags = 0;

    if (sigaction(SIGUSR1, &sa1, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(EXIT_FAILURE);
    }

    // Set up signal handler for SIGUSR2
    sa2.sa_handler = signal_handler_2;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;

    if (sigaction(SIGUSR2, &sa2, NULL) == -1) {
        perror("sigaction SIGUSR2");
        exit(EXIT_FAILURE);
    }

  
    // create a child
    childPid = fork();

    switch (childPid) {
    case -1:
        perror("fork");
        exit(EXIT_FAILURE);

    case 0: /* Child */

        /* Child does some required action here... */

        printf("[%s %ld] Child started - doing some work\n", currTime("%T"), (long)getpid());
        sleep(2); /* Simulate time spent doing some work */

        /* And then signals parent that it's done */

        printf("[%s %ld] Child about to signal parent\n", currTime("%T"), (long)getpid());
        if (kill(getppid(), SYNC_SIG) == -1) {
            perror("kill");
            exit(EXIT_FAILURE);
        }

        /* Now child can do other things... */

        _exit(EXIT_SUCCESS);

    default: /* Parent */

        /* Parent may do some work here, and then waits for child to
           complete the required action */

        printf("[%s %ld] Parent about to wait for signal\n", currTime("%T"), (long)getpid());
        sigemptyset(&emptyMask);
        if (sigsuspend(&emptyMask) == -1 && errno != EINTR) {
            perror("sigsuspend");
            exit(EXIT_FAILURE);
        }
        printf("[%s %ld] Parent got signal\n", currTime("%T"), (long)getpid());

        /* If required, return signal mask to its original state */

        if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1) {
            perror("sigprocmask");
            exit(EXIT_FAILURE);
        }

        /* Parent carries on to do other things... */

        exit(EXIT_SUCCESS);
    }
}