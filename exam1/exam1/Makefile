# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99

# Directories
UNITY_DIR = Unity/src
INCLUDES = -I $(UNITY_DIR)

# Source files
SRC = exam1.c
TEST_SRC = test_exam1.c

# Executable names
TARGET = exam1
TEST_TARGET = test_exam1

# Unity source
UNITY_SRC = $(UNITY_DIR)/unity.c

# # Default target: build the main program
# all: $(TARGET)

# # Build the main exam1 program (without TESTING flag)
# $(TARGET): $(SRC)
# 	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Compile the unit tests with the TESTING flag to exclude the main() function
test: $(TEST_SRC) $(SRC) $(UNITY_SRC)
	$(CC) $(CFLAGS) -DTESTING -o $(TEST_TARGET) $(TEST_SRC) $(SRC) $(UNITY_SRC) $(INCLUDES)

# Run the unit tests
run_tests: test
	./$(TEST_TARGET)

# Clean up the generated files
clean:
	rm -f $(TARGET) $(TEST_TARGET) *.o
