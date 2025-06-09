#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    // File that we will read from
    const char *read_path = "read_test_file.txt";
    // int open(const char *pathname, int flags);
    int read_fd = open(read_path, O_RDONLY);
    if (read_fd == -1)
    {
        perror("Error when using open");
        return 1;
    }
    else
    {
        //printf("File: `%s` Opened successfully\n", read_path);
        printf("File: Opened successfully\n");
    }
    
    char read_buf[100] = {0};
    // ssize_t read(int fd, void *buf, size_t count);
    ssize_t bytes_read = read(read_fd, read_buf, sizeof(read_buf) - 1);
    if (bytes_read == -1)
    {
        perror("Error when using read");
        return 1;
    }
    else
    {        
        printf("Contents of the file (as text):\n");
        for (ssize_t i = 0; i < bytes_read; ++i) {
            putchar(read_buf[i]);
        }
        putchar('\n');  // Optional newline

       
        //read_buf[bytes_read] = '\0';
        //printf("Successfully read: %s\n", read_path);
        //printf("Contents of the file: %s\n", read_buf);
        printf("Able to read Contents of the file:\n");
    }
    close(read_fd);

    char *write_path = "write_test.txt";
    int write_fd = open(write_path, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP
    | S_IWGRP | S_IROTH);
    if (write_fd == -1)
    {
        perror("Error when using open");
        return 1;
    }
    else
    {
        //printf("File: `%s` Opened successfully\n", write_path);
        printf("File: Opened successfully\n");
    }
    // ssize_t write(int fd, const void *buf, size_t count);
    ssize_t bytes_written = write(write_fd, read_buf, bytes_read);
    if (bytes_written == -1)
    {
        perror("Error when using write");
        return 1;
    }
    else
    {
        //printf("Successfully wrote to file: %s\n", write_path);
        printf("Successfully wrote to file:\n");
    }
    
    close(write_fd);
    return 0;
}
