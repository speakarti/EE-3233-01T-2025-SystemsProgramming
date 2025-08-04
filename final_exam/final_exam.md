Final Exam
Due: Wed Aug 6, 2025 11:59pmDue: Wed Aug 6, 2025 11:59pm
Ungraded, 100 Possible Points
100 Points Possible
Attempt


Review Feedback
Offline Score:
N/A

3 Attempts Allowed
Instructions
Use appropriate system calls for file I/O and process management.
You may use any standard library or frameworks provided in the course material.
You must check for errors and handle them appropriately (exiting is fine in most cases).
You may use C/C++ or Python (Can be mixed e.g. problem 1 in C and problem 2 in Python).

## Part 1: File I/O (25 points) ##
Question 1:
Write a program that takes a file name and a string as command-line arguments.

The program should:

1. Takes three command-line arguments:

The first is the name of an input file.
The second is the name of an output file.
Third is a string (e.g “hello world”)
2. Create the output file if it doesn’t exist.

3. Read the input file contents

4. Append the string to the input file contents

5. Write the contents to the output file
6. Display the updated contents of the output file.

Example C usage: ./problem1 input.txt output.txt "hello world"

Example Python usage: python3 problem1.py input.txt output.txt "hello world"

Bonus (5 points): If the file is over 1MB in size, create a backup copy before appending.

## Part 2: Environment Variables (15 points) ##
Question 2:
Write a program that:
1. Checks if an environment variable EXAM_MODE is set.
2. If set to debug, prints process ID and parent process ID.
3. If not set, then sets EXAM_MODE to release and exits.

Example C usage with debug set: EXAM_MODE=debug ./problem2

Example Python usage with debug set: EXAM_MODE=debug python3 problem2.py

Example C usage without debug set: ./problem2

Example Python usage without debug set: python3 problem2.py

## Part 3: Signals (20 points) ##
Question 3:
Write a program that:

Creates a child process using fork().
The child process waits for a signal SIGUSR1.
When the signal is received, the child process prints the PID and PPID and terminates gracefully.
The parent process sends the SIGUSR1 signal to the child process after a 5-second delay.
Requirements: - Handle unexpected signals gracefully in the child process.

## Part 4: Threading (25 points) ##
Question 4:
Write a multi-threaded program where:
1. Spawns n threads, where n is passed as a command-line argument.

2. Each thread calculates the sum from 1 to n and the total is collected.

3. After the threads are completed, the main thread prints the total.

Requirements:

Ensure thread safety when accessing shared resources.
Validate input for the number of threads (n). Should be greater >= 1.
Part 5: Network Communication (15 points)
Question 5:
Write a simple TCP server that:
1. Listens for a connection on a specific port (8080 for example).
2. Receives a string from a client, reverses it, and sends it back.

Write a simple TCP client that:
1. Sends a string to the TCP server.

2. Receives the reversed string from the server and prints it.

Bonus (5 points): Write a corresponding TCP server/client program in C and/or Python. If you wrote the client/server in C, then bonus for writing again in Python. (2.5pts for server and 2.5pts for client) and vice verse.

Total Points:
110 (100 main + 10 bonus)