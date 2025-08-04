#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    /* code */
    printf("MAIN PROCESS BEFORE FORK: pid %d, its parent pid %d. \n", (int) getpid(), (int) getppid());
    printf("[PID %d] Parent process. Parent PID = %d.\n", (int) getpid(), (int) getppid());

    //printf("[PID %d] Parent process. Child PID = %d.\n", (int) getpid(), (int) pid_child);

    // forking a child process
    int pid_child = fork(); // fork will create child and return pid of child 
    if (pid_child < 0) {
         // Fork failed
        perror("fork failed");
        return 1;
    }
    else if (pid_child == 0)
        printf("CHILD RUNNING: current pid %d, its parent pid %d. \n", (int) getpid(), (int) getppid());
    else {
        // parent will have pid_child after fork
        printf("PARENT RUNNING: current pid %d, its parent pid %d. \n", (int) getpid(), (int) getppid());   

        // Wait for the child to finish
        int status;
        waitpid(pid_child, &status, 0);

        if (WIFEXITED(status)) {
            printf("PARENT: child %d exited with status %d.\n", pid_child, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("PARENT: child %d killed by signal %d.\n", pid_child, WTERMSIG(status));
        } else {
            printf("PARENT: child %d ended abnormally.\n", pid_child);
        }
        printf("PARENT CONTINUES: pid %d after child completion.\n", (int)getpid());
    }

    return 0;
}

