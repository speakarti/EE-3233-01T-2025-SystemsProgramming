#!/usr/bin/python3
import sys
import subprocess

'''
Problem Statment: Submit your solutions on canvas.
1. Write a C or Python program that makes use of Popen. You will use Popen to
echo “Hello World” into a file and Popen to read (25 points):
a. Use Popen to execute an echo command to write to a file.
    a. Print “Using popen to echo ‘Hello World’ to a file”
    b. The file should be called test.txt
b. Use Popen to read the contents of a file of the file using cat
    a. Print “Using popen to cat test.txt”
    b. Read contents of text.txt using cat
    c. Print the contents to screen

(BONUS) 10 pts
c. Use command line args in place of the “Hello World” and “test.txt”
'''


'''
Expected bonus response if using python:
$ python3 hw6_1.py "abc123" mytestfile.txt
“Using popen to echo ‘abc123’ to a file”
“Using popen to cat mytestfile.txt”
“mytestfile.txt contains ‘abc123’”
'''
def main():
    argc = len(sys.argv)
    args = sys.argv
    if argc == 3:
        filename=args[2]
        filecontents=args[1]   
    else:
        print(f"Using default values for contents and filename as per instructions")
        filename="test.txt"
        filecontents='Hello World' 
    
    print(f"arguments array is : {args}")

    print(f"Using popen to echo '{filecontents}' to a file '{filename}'")

    #open file in write mode, using with context, this will help in closing file automatically
    with open(filename,'w') as fh:
        return_process = subprocess.Popen(['echo',filecontents],stdout=fh) #launch a subprocess i.e. shell echo and redirects stdoutput from default terminal to file handler fh.
        stdout, stderr = return_process.communicate() #wait for subprocess to complete, it returns a tuple of stdout and stderr for further tracking/exceptino handling etc.
    
    print(f"Using popen to read of a file '{filename}' using 'cat' command")
    #open file in read mode, using with context, this will help in closing file automatically
    with open(filename,'r') as fh:
        return_process = subprocess.Popen(['cat',filename]) #launch a sßubprocess i.e. shell echo and redirects stdoutput from default terminal to file handler fh.
        stdout, stderr = return_process.communicate() #wait for subprocess to complete
        if(stdout or stderr):
            print(f"prinitng stdout and std err {stdout},{stderr}")

if __name__ == '__main__':
    main()