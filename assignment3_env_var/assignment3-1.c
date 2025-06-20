#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // Step 1
    // Pass in your student id via command line argument.
    // grab command line arguments
    printf("total number of arguments passsed with script including script name are : argc: %d\n", argc);
    printf("script (full path with name): argv[0]: %s\n", argv[0]); // this is script name
    printf("student_id : argv[1]:  %s\n", argv[1]); // this is first argument passed in script
    
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <student_id>\n", argv[0]);
        return 1;
    }

    // create a string having env var name and value 
    char user_id[100];
    snprintf(user_id, sizeof(user_id), "USER_ID=%s", argv[1]);
    printf("going to set USER_ID as environment variable with value as %s using putenv()\n", user_id);

    //set env variable
    if (putenv(user_id) != 0) {
        perror("Failed to set USER_ID");
        return 1;
    } else {
        printf("Got the Value of environment varibale USER_ID using getenv() as %s, this was set using putenv()\n", getenv("USER_ID"));
    }

    // Step 2: Set ASSIGNMENT3
    char *assignment_str = "ASSIGNMENT3=Environment Variables and Process IDs";
    if (putenv(assignment_str) != 0) {
        perror("Failed to set ASSIGNMENT3");
        return 1;
    } else {
        printf("ASSIGNMENT3 is %s using putenv\n", getenv("ASSIGNMENT3"));
    }

    // Step 3
    // Write code to get your process's ID (PID)
    // Example code to convert int to char[]
    // char pid_str[8] = {0};
    // sprintf(pid_str, "%d", <variable used for getpid>);
    // Step 3: Get PID
    pid_t pid = getpid();
 
    // Step 4
    // Set environment variable MY_PID to the PID found above
    // Print the PID
    char pid_env[50];
    snprintf(pid_env, sizeof(pid_env), "MY_PID=%d", pid);
    if (putenv(pid_env) != 0) {
        perror("Failed to set MY_PID");
        return 1;
    } else {
        printf("MY_PID is %s using putenv\n", getenv("MY_PID"));
    }
 
    // Step 5
    // An environment variable named "COURSE_NAME" is available, as its being set using EXPORT command throung shell script
    // Print the value
    // Change it to the correct course name (EE3233 Systems Programming)
    // Print it again
    // Step 5: Update COURSE_NAME
    // Assume it's already in environment
    char *course_val = getenv("COURSE_NAME");
    if (course_val)
        printf("Retreived environment variable: COURSE_NAME: %s\n", course_val);
    else
        printf("COURSE_NAME not set initially.\n");
    
    // Now set it
    char *course_str = "COURSE_NAME=EE3233 Systems Programming";
    if (putenv(course_str) != 0) {
        perror("Failed to set COURSE_NAME");
        return 1;
    } else {
        printf("COURSE_NAME after setting is: %s\n", getenv("COURSE_NAME"));
    }


    return 0;
}