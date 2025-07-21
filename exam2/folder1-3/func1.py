#!/usr/bin/python3
import os
import sys

def func1(startdir):
    for (thisDir, dirsHere, filesHere) in os.walk(startdir):
        for fname in filesHere:
            fpath = os.path.join(thisDir, fname)
            print(fpath)


if __name__ =='__main__':
    func1(sys.argv[1])
