### Assignment 5: Signal Synchronization between Processes
## Objective: Implement signal synchronization between parent and child processes.

Parent Process:

Signal Mask:

Before calling fork(), modify the parent process's signal mask to block SIGUSR1 and SIGUSR2.

Signal Handlers:

Use the sigaction() function to set up signal handlers (signal_handler_1() for SIGUSR1 and signal_handler_2() for SIGUSR2).

signal_handler_1() should print: "Child received SIGUSR1!\n".

signal_handler_2() should print: "Parent received SIGUSR2!\n".

Process Execution:

Once initialized, the parent should print: "Parent started...\n".

Sleep for 3 seconds.

Print: "Parent about to signal child...\n".

Send the SIGUSR1 signal to the child process.

Print a message (e.g., "Hello from Parent!\n") to the pipe for the child to read.

Wait for SIGUSR2 from the child.

Print a final message and then exit.

Error Handling:

Handle any errors that may occur in system calls. If an error occurs, print an appropriate error message and exit gracefully.

Child Process:

Signal Mask Reset:

At the start, replace the child's signal mask with an empty set. This allows it to receive SIGUSR1 and SIGUSR2.

Signal Handlers:

Use sigaction() to set up signal handlers (signal_handler_1() for SIGUSR1).

signal_handler_1() should print: "Child received SIGUSR1!\n".

Wait for Signal:

Suspend the child's execution, waiting for the SIGUSR1 signal from the parent process (using pause() or a similar function).

Upon receiving SIGUSR1, read the message from the pipe and print it.

Send SIGUSR2 back to the parent.

Signal Receipt:
Upon receiving the SIGUSR1 signal, the child should print: "Child received signal!\n" and exit
Expected Output:

Parent process should output:

"Parent started..."

"Parent about to signal child..."

"Parent received SIGUSR2!"

"Goodbye from Parent (PID: )"

Child process should output:

"Child received SIGUSR1!"

"Goodbye from Child (PID: )"