# CSC_521_ASG_SOL
Assignment solution for Advance Programming language

This is a sample solution i came up with for my assignment

![image](https://github.com/vishnugupthaa/CSC_521_ASG_SOL/assets/60147011/81d25e05-d038-4bd0-89e0-9cec118412f9)

STEPS TO RUN THE CODE:
=====================
1. EXTRACT THE .ZIP 
2. COMPILE 'Parser.c' USING CMD BY USING "gcc parser.c scanner.c -o parser"
3. RUN 'Parser.c' USING "./parser <filename>" or "parser <filename>"

Project Details:
===============
When you compile the code,
    It will create a file named 'parser.exe'
When you run the code,
    It will show you the appropriate output of the <filename> given
Procedure:
===========

1. Initially the code reads '<filename>' as input and using scan() from "scanner.c", code checks the valid comments 
    and moves forward with the remaining contents in '<filename>'.
2. Then the code checks for errors in the '<filename>' and gives out the error message as output.
