#!/usr/bin/env python3

# writer.py
import sys
import random

function = "nop_slide"

def main():
    # File.
    f = open(f"{function}.S", 'w')

    # Directives.
    f.write("  .text\n\n")
    f.write(f"  .global {function}\n")
    f.write(f"  .type   {function}, @function\n")
    f.write(f"{function}:\n")

    # Function prologue.
    f.write("  pushq %rbp\n")
    f.write("  movq %rsp, %rbp\n")

    # Read TSC - start.
    f.write("  rdtscp\n")
    f.write("  movl %eax, %ebx\n")

    ## new code to print nop or fnop in random node
    commands = ["nop", "fnop"]
    count = random.randint(5, 15)  # choose between 5 and 15 ops
    for _ in range(count):
        command = random.choice(commands)
        f.write(f"  {command}\n")

        
    n=10
    list_commands = random.choices(["nop", "fnop"], k=n)
    for command in list_commands:
        f.write(f"  {command}\n")

    # Read TSC - end.
    f.write("  rdtscp\n")
    f.write("  subl %ebx, %eax\n")

    # Function epilogue.
    f.write("  popq %rbp\n")
    f.write("  retq\n")

    f.close()
    

if __name__ == "__main__":
        main()

