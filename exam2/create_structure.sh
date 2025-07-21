#!/bin/bash

# Create files in current directory
echo "123456" > 2.py
echo "some text" > foo.txt
echo "# func1 without target string" > func1.py
echo "def func2(): return 123456" > func2.py

# Create subdirectory
mkdir -p myDir
echo "123456" > myDir/abc.txt

# Set permissions (optional, matches your example)
chmod 664 2.py foo.txt func1.py func2.py myDir/abc.txt
chmod 775 myDir

# Done
echo "Files and folder created successfully."
