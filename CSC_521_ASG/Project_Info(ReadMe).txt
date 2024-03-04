ADVANCED PROGRAMMING CSC_521
=====================
This project was done by:

TEAM:
=====
o	VISHNUGUPTHAA RAMIDI  [212238054]
o	TEJA VENKATA SAI PAVAN KOPPISETTY  [212231827]
o	YASWANTH KATUKOTA  [212240199]

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

Output:
=======
For file "prog1":

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog1
    No Lexical or Syntax errors 
    The Calculator Program Runs Perfectly Fine
For file "prog2":

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog2
    lexical error on line no 7
    unclosed comment
For file "prog3":

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog3
    syntax error on line no 1 
For file "prog4":

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog4
    syntax error on line no 2 
For file "prog5":

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog5
    syntax error on line no 5

EXTRA CREDITS OUTPUT:
======================

1. 
    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog5
    syntax error on line no 5 
2.
    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog6
    lexical error on line no 4
    An unexpected character got in the program

    C:\Users\vramidi1\Documents\codes\Ramidi_Katukota_Koppisetty_521_proj2>parser prog7
    lexical error on line no 4
    The symbol '=' is missing check the code once again

Procedure:
===========

1. Initially the code reads '<filename>' as input and using scan() from "scanner.c", code checks the valid comments 
    and moves forward with the remaining contents in '<filename>'.
2. Then the code checks for errors in the '<filename>' and gives out the error message as output.

CONTRIBUTION:
=============
VISHNUGUPTHAA_RAMIDI ---> ENTIRE TASK 1
PAVAN_KOPPISETTY ---> ENTIRE TASK2
YASWANTH_KATUKOTA ---> EXTRA CREDITS TASKS AND TASK 2

PROBLEMS FACED:
===============
Entire task 2 is too difficult to code in C language as the C-programming is an old language and even the regex and table 
creation was too much of a hectic work.Can you please consider the work it takes when you give out the future assignments.