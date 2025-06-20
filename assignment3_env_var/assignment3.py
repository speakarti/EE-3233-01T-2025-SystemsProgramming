#!/usr/bin/env python3
import os
import sys

def commandline_param_passing():
    # Step 1: Pass student ID via command line
    argc = len(sys.argv)
    print(f"Total number of arguments passed with script including script name: argc = {argc}")
    print(f"Script (full path with name): argv[0]: {sys.argv[0]}")
    
    if argc < 2:
        print(f"Usage: {sys.argv[0]} <student_id>")
        return 1
    
    student_id = sys.argv[1]
    print(f"Student ID: argv[1]: {student_id}")
    
    # Set USER_ID environment variable
    os.environ['USER_ID'] = student_id
    print(f"Going to set USER_ID as environment variable with value: {student_id}")
    print(f"Got the value of environment variable USER_ID using os.environ: {os.environ.get('USER_ID')}")

    # Step 2: Set ASSIGNMENT3
    os.environ['ASSIGNMENT3'] = "Environment Variables and Process IDs"
    print(f"ASSIGNMENT3 is {os.environ.get('ASSIGNMENT3')} using os.environ")

    # Step 3: Get PID
    pid = os.getpid()

    # Step 4: Set MY_PID
    os.environ['MY_PID'] = str(pid)
    print(f"MY_PID is {os.environ.get('MY_PID')} using os.environ")

    # Step 5: Read, update, and print COURSE_NAME
    course_name = os.environ.get("COURSE_NAME")
    if course_name:
        print(f"Retrieved environment variable COURSE_NAME: {course_name}")
    else:
        print("COURSE_NAME not set initially.")

    os.environ["COURSE_NAME"] = "EE3233 Systems Programming"
    print(f"COURSE_NAME after setting is: {os.environ.get('COURSE_NAME')}")

    return 0




if __name__ == "__main__":
    commandline_param_passing()
