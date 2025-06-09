// a C program named multiple_copies that copies the contents of a source file to two specified destination files. 
// using system calls (open, read, write and close).
// Build Instructions: gcc multiple_copies.c -o multiple_copies
// Run Instructions: ./multiple_copies source_file destination_file1 destination_file2
// Run Instructions: ./multiple_copies "read_test_file.txt" "destination_file1.txt" "destination_file2.txt"
// Example: /multiple_copies input.txt copy1.txt copy2.txt

/*
Requirements:
1. Input Arguments: The program should accept three command-line arguments:
    source_file: The file whose contents need to be copied.
    destination_file1: The first file where the contents will be copied to.
    destination_file2: The second file where the contents will be copied to.

2. Argument Count Check: The program should check if exactly three arguments (excluding the program name) are provided. If not, it should display the following error message:
    Usage: multiple_copies source_file destination_file1 destination_file2

3. Source File Existence Check: Before attempting to copy, the program should check if the source_file exists. If it doesn't, display an error message:
    Opening Error!: [source_file_name]
    Replace [source_file_name] with the actual name of the source file provided.

4. Destination File Overwrite: If either of the destination files already exists, the program should overwrite its contents without any prompt.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    //check count of arguments passed in command line, exit if less than 4.
    if (argc != 4) {
        fprintf(stderr, "ERROR: Command Usage : ./multiple_copies source_file destination_file1 destination_file2 \n");
        return 1;
    }

    // assign appropriate file names as per arguments passed.
    const char *source_file = argv[1];
    const char *destination_file1 = argv[2];
    const char *destination_file2 = argv[3];

    //open source_file in readonly mode, it will return a valid file descriptor.
    // int open(const char *pathname, int flags);
    int read_fd = open(source_file, O_RDONLY);
    if (read_fd == -1)
    {        
        fprintf(stderr, "Opening Error!: %s\n", source_file);
        perror("Reason");
        //perror("Error: when using opening source_file.");
        return 1;
    }
    else
    {
        printf("File: source_file Opened successfully.\n");
    }
    

    //open destination_file1 in 'write' mode.
    // "Open the file for writing. If it doesn’t exist, create it with permissions 664 (rw-rw-r--). If it already exists, truncate it.
    // int open(const char *pathname, int flags);
    int write_fd1 = open(destination_file1, O_WRONLY | O_CREAT, S_IWUSR, O_TRUNC | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH );
    if (write_fd1 == -1)
    {
        perror("Error: when opening destination_file1");
        return 1;
    }
    else
    {
        printf("File: destination_file1 Opened successfully\n");
    }


    //open destination_file2 in 'write' mode.
    // int open(const char *pathname, int flags);
    int write_fd2 = open(destination_file2, O_WRONLY | O_CREAT, S_IWUSR, O_TRUNC | S_IRUSR | S_IRGRP | S_IWGRP | S_IROTH );
    if (write_fd2 == -1)
    {
        perror("Error: when opening destination_file2");
        return 1;
    }
    else
    {
        printf("File: destination_file2 Opened successfully\n");
    }

    //read 1024 bytes of data in one cycle
    char buffer[1024]; //already allocated a buffer of size 1024 bytes
    ssize_t bytes_read;

    //read will return > 0 as number of bytes it read, 0 as End of file, and -1 as error
    // it will read contents of file of size (buffer) into buffer.
    while ((bytes_read = read(read_fd, buffer, sizeof(buffer))) > 0) {
        if (write(write_fd1, buffer, bytes_read) != bytes_read || write(write_fd2, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination files");
            close(read_fd);
            close(write_fd1);
            close(write_fd2);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
    } else {
        printf("File copied successfully to both destinations.\n");
    }

    // close 
    close(read_fd);
    close(write_fd1);
    close(write_fd2);
    return 0;
}
