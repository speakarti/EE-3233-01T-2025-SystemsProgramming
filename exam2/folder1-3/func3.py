#!/usr/bin/python3
import os
import fnmatch

startdir = "."


for (thisDir, dirsHere, filesHere) in os.walk(startdir):
    for fname in dirsHere + filesHere:
        
        if fnmatch.fnmatch(fname, "*.txt"):
            print(fname)

