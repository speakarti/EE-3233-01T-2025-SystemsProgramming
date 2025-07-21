#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

#define PID_MAX_PATH "/proc/sys/kernel/pid_max"

// Write a program utilizing fork() to update /proc/sys/kernel/pid_max.
// 1.(5pts) Use command line args to input desired value
// 2.(5pts) The child process will read the old value, print it, andupdate the value 
//      (Remember to use a value <= to the oldpid_max).
// 3.(5pts) The parent will read and print the new value. 
//      (you mightneed to run your program with sudo to change the value)
// 4.(15pts) You must use proper error handling for all libraryfunctions/system calls.


// cat /proc/sys/kernel/pid_max
// 4194304

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

// read current value from pid_max file.
long read_pid_max() {
    //open file in read mode, and return file pointer fp
    FILE *fp = fopen(PID_MAX_PATH, "r");
    if (!fp) {
        error_exit("Failed to open pid_max in read mode.");
    }
    
    // read value from fp in a a long variable
    long pid_max_value;
    if (fscanf(fp, "%ld", &pid_max_value) != 1) {
        fclose(fp);
        error_exit("Failed to read pid_max");
    }

    fclose(fp); // close file pointer after read.
    return pid_max_value; //return value
}

//function to update pid_max_value in file.
void write_pid_max(long pid_max_value) {
    //open file in write mode, and return file pointer fp
    FILE *fp = fopen(PID_MAX_PATH, "w");
    if (!fp) {
        error_exit("Failed to open pid_max in write mode.");
    }

    if (fprintf(fp, "%ld\n", pid_max_value) < 0) {
        fclose(fp);
        error_exit("Failed to write new pid_max");
    }

    fclose(fp);
}


// main fucntion
int main(int argc, char *argv[]) {

    // need to pass total of two parameters command and new value for max_pid
    if (argc != 2) {
        fprintf(stderr, "Usage: sudo %s <new_pid_max>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Convert command-line argument from string to long "4000" to 4000, and for "mystring" new_value to 0. 
    char *endptr;
    long new_value = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || new_value <= 0) {
        fprintf(stderr, "Invalid value for pid_max: %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    if (child_pid < 0) {
        error_exit("failed to fork a new process.");
    }

    if (child_pid == 0) {
        // logic for Child process as this wil have child_pid==0, but parent will hve a number
        long old_value = read_pid_max();
        printf("[Child] Old pid_max: %ld\n", old_value);

        // Validate to ensure new value is less than and equal to old value.
        if (new_value > old_value) {
            fprintf(stderr, "[Child] New pid_max must be <= old pid_max (%ld)\n", old_value);
            exit(EXIT_FAILURE);
        }

        write_pid_max(new_value);
        printf("[Child] Updated pid_max to %ld\n", new_value);
        exit(EXIT_SUCCESS);
    } else {
        // Parent process havign a value of child_pid != 0
        int status;

        //wait for child to finish changing max_pid
        if (wait(&status) == -1) {
            error_exit("wait failed");
        }

        // Parent is reading and printing max_pix value reset by child process.
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            long new_value = read_pid_max();
            printf("[Parent] New pid_max: %ld\n", new_value);
        } else {
            fprintf(stderr, "[Parent] Child process failed or exited abnormally\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
