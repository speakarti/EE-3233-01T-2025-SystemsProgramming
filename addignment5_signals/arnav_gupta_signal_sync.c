#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int comm_pipe[2]; // Used for message exchange between child and parent
pid_t spawned_pid = -1;

/*
Signal Processing Functions:
Configure handlers using sigaction().
handle_usr1() responds to SIGUSR1 and handle_usr2() handles SIGUSR2.
Expected outputs must not be changed.
*/

void handle_usr1(int sig) {
    if (getpid() == spawned_pid) {
        printf("Child received SIGUSR1!\n");
    } else {
        printf("Parent received SIGUSR1!\n");
    }
}

void handle_usr2(int sig) {
    printf("Parent received SIGUSR2!\n");
}

int main() {
    sigset_t blocked_signals, sig_clear;
    struct sigaction act_usr1, act_usr2;

    // Initialize pipe for data transmission
    if (pipe(comm_pipe) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Temporarily block SIGUSR1 and SIGUSR2 before forking
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGUSR1);
    sigaddset(&blocked_signals, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &blocked_signals, NULL) == -1) {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }

    // Set handler for SIGUSR1
    act_usr1.sa_handler = handle_usr1;
    sigemptyset(&act_usr1.sa_mask);
    act_usr1.sa_flags = 0;

    if (sigaction(SIGUSR1, &act_usr1, NULL) == -1) {
        perror("sigaction SIGUSR1");
        exit(EXIT_FAILURE);
    }

    // Set handler for SIGUSR2
    act_usr2.sa_handler = handle_usr2;
    sigemptyset(&act_usr2.sa_mask);
    act_usr2.sa_flags = 0;

    if (sigaction(SIGUSR2, &act_usr2, NULL) == -1) {
        perror("sigaction SIGUSR2");
        exit(EXIT_FAILURE);
    }

    // Fork the process
    spawned_pid = fork();
    if (spawned_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (spawned_pid == 0) {
        // === Child Execution Path ===

        // Unblock all signals for the child
        sigemptyset(&sig_clear);
        if (sigprocmask(SIG_SETMASK, &sig_clear, NULL) == -1) {
            perror("sigprocmask child");
            exit(EXIT_FAILURE);
        }

        // Close write end of the pipe
        close(comm_pipe[1]);

        // Pause to receive signal
        pause();

        // Read incoming message from pipe
        char msg_buf[100];
        ssize_t msg_len = read(comm_pipe[0], msg_buf, sizeof(msg_buf) - 1);
        if (msg_len > 0) {
            msg_buf[msg_len] = '\0';
            printf("%s", msg_buf);
        } else {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Notify parent via SIGUSR2
        kill(getppid(), SIGUSR2);

        printf("Goodbye from Child (PID: %d)\n", getpid());

        close(comm_pipe[0]);
        exit(EXIT_SUCCESS);
    } else {
        // === Parent Execution Path ===

        printf("Parent started...\n");
        sleep(3);

        printf("Parent about to signal child...\n");

        // Send signal to child
        if (kill(spawned_pid, SIGUSR1) == -1) {
            perror("kill SIGUSR1");
            exit(EXIT_FAILURE);
        }

        // Parent writes message to pipe
        close(comm_pipe[0]); // Only writing
        const char *msg = "Hello from Parent!\n";
        if (write(comm_pipe[1], msg, strlen(msg)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        close(comm_pipe[1]);

        // Wait for child to notify via SIGUSR2
        sigemptyset(&sig_clear);
        sigsuspend(&sig_clear); // Temporarily unblock all

        printf("Goodbye from Parent (PID: %d)\n", getpid());

        wait(NULL); // Wait for child termination
        exit(EXIT_SUCCESS);
    }
}