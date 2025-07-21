# Code for assignment 4 to handle file operations like search and get details
# written by Arnav Gupta
# this code works in Linux /Ubuntu
# for windows we need to use differenet libaries

#!/usr/bin/python3
import os
from pathlib import Path
import stat
import pwd #doesn't work in windows
import sys
import grp #doesn't work in windows

def get_files(extn:str, folder:str) -> list:
    folderpath= Path(folder)
    ll = [str(file) for file in folderpath.glob(f'*{extn}') if file.is_file()]
    return ll

def get_file_stats(file:str) -> list:
    file_stat = os.stat(file)
    permissions = oct(file_stat.st_mode)[-3:]
    owner = pwd.getpwuid(file_stat.st_uid).pw_name
    group = grp.getgrgid(file_stat.st_gid).gr_name
    return permissions, owner, group

def search_file(filename, search_word):
    with open(filename, 'r') as file:
        content = file.read()
        if search_word in content:
            return True
        return False

if __name__ == '__main__':
    #read all command line arguments passed while executing script
    argc = len(sys.argv)
    if argc == 4 and sys.argv[1] == 'details':
        # <operation>: The type of operation you want the program to perform ("details" or "search").
        # <ext>: The file extension to filter by within the specified directory.
        # <directory>: The directory where the operation will be performed.
        # <search_keyword>: (Optional) A keyword to search for within the files. Required if <operation> is "search".

        print (f"Number of Arguments passed are : {argc}")
        for i in range(argc):
            print (f"{i}th Argument sys.argv[{i}] is :" + sys.argv[i])
        files = get_files(sys.argv[2], sys.argv[3])
        print (f"files are {files}")
        for file in files:
            stats = get_file_stats(file)
            print(stats)
    elif argc == 5 and sys.argv[1] == 'search':
        print (f"Number of Arguments passed are : {argc}")
        files = get_files(sys.argv[2], sys.argv[3])
        print (f"files are {files}")
        for file in files:
            if search_file(file, sys.argv[4]):
                print(f"Keyword {sys.argv[4]} found in: {file}")
    else:
        print (f"Pls follow command syntax: $ python3 {sys.argv[0]} <operation> <ext> <directory> [<search_keyword>]")
