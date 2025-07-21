#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int pipefd[2]; // Pipe for parent to write and child to read
pid_t childpid = -1;

/*
Signal Handlers:
Use the sigaction() function to set up signal handlers (signal_handler_1() for SIGUSR1 and signal_handler_2() for SIGUSR2).
signal_handler_1() should print: "Child received SIGUSR1!\n".
signal_handler_2() should print: "Parent received SIGUSR2!\n".
*/

void signal_handler_1(int sig) {
    if (getpid() == childpid) {
        printf("Child received SIGUSR1!\n");
    } else {
        printf("Parent received SIGUSR1!\n");
    }
}

void signal_handler_2(int sig) {
    printf("Parent received SIGUSR2!\n");
}

int main() {
    sigset_t block_mask, empty_mask;
    struct sigaction sa1, sa2;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Block SIGUSR1 and SIGUSR2 before fork
    sigemptyset(&block_mask);
    sigaddset(&block_mask, SIGUSR1);
    sigaddset(&block_mask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &block_mask, NULL) == -1) {
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

    childpid = fork();
    if (childpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childpid == 0) {
        // === Child Process ===

        // Replace signal mask with empty set
        sigemptyset(&empty_mask);
        if (sigprocmask(SIG_SETMASK, &empty_mask, NULL) == -1) {
            perror("sigprocmask child");
            exit(EXIT_FAILURE);
        }

        // Close unused write end
        close(pipefd[1]);

        // Wait for signal
        pause();

        // Read message from pipe
        char buffer[100];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';
            printf("%s", buffer);
        } else {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Send SIGUSR2 to parent
        kill(getppid(), SIGUSR2);

        printf("Goodbye from Child (PID: %d)\n", getpid());

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // === Parent Process ===

        printf("Parent started...\n");
        sleep(3);

        printf("Parent about to signal child...\n");

        // Send SIGUSR1 to child
        if (kill(childpid, SIGUSR1) == -1) {
            perror("kill SIGUSR1");
            exit(EXIT_FAILURE);
        }

        // Write to pipe
        close(pipefd[0]); // Close unused read end
        const char *msg = "Hello from Parent!\n";
        if (write(pipefd[1], msg, strlen(msg)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(pipefd[1]);

        // Wait for SIGUSR2 from child
        sigemptyset(&empty_mask);
        sigsuspend(&empty_mask); // Wait for any unblocked signal

        printf("Goodbye from Parent (PID: %d)\n", getpid());

        wait(NULL); // Wait for child to finish
        exit(EXIT_SUCCESS);
    }
}