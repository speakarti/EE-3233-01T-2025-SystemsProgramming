import subprocess
import sys

# Defaults
message = "Hello World"
filename = "test.txt"

# BONUS: Accept command-line arguments if provided
if len(sys.argv) >= 2:
    message = sys.argv[1]
if len(sys.argv) >= 3:
    filename = sys.argv[2]

# Part a: Write to file using echo and popen
print(f"Using popen to echo '{message}' to a file")

# Open file in write mode and use echo to write to it
with open(filename, 'w') as f:
    echo_process = subprocess.Popen(['echo', message], stdout=f)
    echo_process.communicate()

# Part b: Read from file using cat and popen
print(f"Using popen to cat {filename}")

cat_process = subprocess.Popen(['cat', filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
stdout, stderr = cat_process.communicate()

# Print output
if cat_process.returncode == 0:
    print("Contents of the file:")
    print(stdout.decode())
else:
    print("Error reading file:", stderr.decode())
