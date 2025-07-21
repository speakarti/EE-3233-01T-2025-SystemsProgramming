#include "unity.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

// Include the functions you want to test
extern int copy_file(const char *source, const char *destination);
extern const char *get_env_var(const char *var_name);
extern int set_env_var(const char *var_name, const char *value, int overwrite);

// Helper function to create a file with some content
void create_test_file(const char *filename, const char *content)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, content, sizeof(char) * strlen(content));
    close(fd);
}

// Unit test for successful file copy and permission check
void test_copy_file_success(void)
{
    const char *source = "test_source.txt";
    const char *destination = "test_destination.txt";

    // Create a source file with some content
    create_test_file(source, "Hello, world!");

    // Copy the file
    TEST_ASSERT_EQUAL(0, copy_file(source, destination));

    // Verify the destination file content matches
    char buffer[20];
    int dest_fd = open(destination, O_RDONLY);
    int n_read = read(dest_fd, buffer, sizeof(buffer) - 1);
    buffer[n_read] = '\0'; // Null terminate

    TEST_ASSERT_EQUAL_STRING("Hello, world!", buffer);
    close(dest_fd);

    // Verify that the destination file has 0644 permissions
    struct stat file_stat;
    stat(destination, &file_stat);
    TEST_ASSERT_EQUAL_INT(0644, file_stat.st_mode & 0777); // Check file permissions

    // Clean up files
    remove(source);
    remove(destination);
}

// Unit test for missing source file
void test_copy_file_no_source(void)
{
    const char *source = "non_existent_file.txt";
    const char *destination = "test_destination.txt";

    // Attempt to copy a non-existent file
    TEST_ASSERT_EQUAL(-1, copy_file(source, destination));
}

// Unit test for failing to write to a read-only destination file
void test_copy_file_readonly_destination(void)
{
    const char *source = "test_source.txt";
    const char *destination = "test_readonly_dest.txt";

    // Create a source file with content
    create_test_file(source, "This should fail.");

    // Create a destination file and make it read-only
    create_test_file(destination, "");
    chmod(destination, 0444); // Set destination file to read-only

    // Attempt to copy the file; it should fail due to write permissions
    TEST_ASSERT_EQUAL(-1, copy_file(source, destination));

    // Check errno to ensure it's a permission error
    TEST_ASSERT_EQUAL_INT(EACCES, errno);

    // Clean up files
    remove(source);
    remove(destination);
}

// Unit test for failing to read from a write-only source file
void test_copy_file_write_only_source(void)
{
    const char *source = "test_write_only_source.txt";
    const char *destination = "test_destination.txt";

    // Create a source file and set it to write-only
    create_test_file(source, "This file has write-only permissions.");
    chmod(source, 0222); // Set source file to write-only (no read permissions)

    // Attempt to copy the file; it should fail due to read permissions
    TEST_ASSERT_EQUAL(-1, copy_file(source, destination));

    // Check errno to ensure it's a permission error
    TEST_ASSERT_EQUAL_INT(EACCES, errno);

    // Clean up files
    remove(source);
    remove(destination);
}

// Test for setting environment variables
void test_set_env_var(void)
{
    // Set the environment variable
    int result = set_env_var("MY_VAR", "42", 1);
    TEST_ASSERT_EQUAL(0, result); // Ensure the setenv call was successful

    // Verify that the environment variable is set correctly
    const char *value = getenv("MY_VAR");
    TEST_ASSERT_NOT_NULL(value);           // Ensure the variable exists
    TEST_ASSERT_EQUAL_STRING("42", value); // Ensure it has the right value

    // Update the environment variable
    result = set_env_var("MY_VAR", "99", 1);
    TEST_ASSERT_EQUAL(0, result); // Ensure the setenv call was successful

    // Verify that the environment variable is updated
    value = getenv("MY_VAR");
    TEST_ASSERT_EQUAL_STRING("99", value);

    // Unset the environment variable
    unsetenv("MY_VAR");

    // Verify that the variable is no longer set
    value = getenv("MY_VAR");
    TEST_ASSERT_NULL(value); // It should now return NULL
}

// Test for getting environment variables
void test_get_env_var(void)
{
    // Set an environment variable for testing
    setenv("TEST_ENV", "TestValue", 1);

    // Check if the environment variable is retrieved correctly
    const char *value = get_env_var("TEST_ENV");
    TEST_ASSERT_EQUAL_STRING("TestValue", value);

    // Test a non-existent environment variable
    value = get_env_var("NON_EXISTENT_ENV");
    TEST_ASSERT_EQUAL_STRING("Environment variable not found", value);

    // Unset the environment variable after the test
    unsetenv("TEST_ENV");
}

// Unity setup and teardown functions (optional)
void setUp(void) {}
void tearDown(void) {}

// Main function to run all tests
int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_copy_file_success);
    RUN_TEST(test_copy_file_no_source);
    RUN_TEST(test_copy_file_readonly_destination);
    RUN_TEST(test_copy_file_write_only_source);
    RUN_TEST(test_set_env_var);
    RUN_TEST(test_get_env_var);

    return UNITY_END();
}
