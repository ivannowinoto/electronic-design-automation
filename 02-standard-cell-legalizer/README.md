# Programming Assignment 2: Single-Row-Height Cell Legalization

Programming Language
----------------------------------------------------
C++

Compilation Platform
----------------------------------------------------
Linux — GNU g++ compiler

File Descriptions
----------------------------------------------------
main.cpp        : Main source file containing the program entry point
io.cpp          : Source file handling all input and output operations
legalizer.cpp   : Source file implementing cell legalization functions
legalizer.h     : Header file defining data structures and declarations
Makefile        : Makefile for automatic compilation
README.md       : This documentation file
report.docx     : Report explaining data structures and algorithms used
pa2.txt			: Summarized version of the original problem statement

Compilation Instructions
----------------------------------------------------
1. Open a terminal and navigate to the project directory.
2. Run the following command:
       make
   This will automatically compile all source files and generate
   the executable file named 'legalizer'.

Execution and Usage Instructions
----------------------------------------------------
1. Ensure that the 'legalizer' executable file has been successfully generated.
2. Confirm that the input file (e.g., case1.def) is located in the same folder.
3. Run the program using the following command format:
       ./legalizer [cell width (in terms of sites)] [alpha] [input file name] [output file name]

   Example:
       ./legalizer 2 2 case1.def output.txt

4. After execution, the program will generate an output file (e.g., output.txt)
   in the same directory.

   The output file contains the legalized placement results and follows
   the same format as the input file.
