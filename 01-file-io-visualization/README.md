# Programming Assignment 1: Physical Circuit Design Visualization

Programming Language
----------------------------------------------------
C++

Compilation Platform
----------------------------------------------------
Linux — GNU g++ compiler

File Descriptions
----------------------------------------------------
main.cpp        : Main source file containing the program entry point
genPlot.cpp     : Source file implementing main functions
genPlot.h       : Header file defining structs and function declarations
Makefile        : Makefile for automatic compilation
README.md	    : This documentation file
pa1_testcases   : Input file test cases
output_sample   : Example output image (PNG) generated using Gnuplot
pa1.txt			: The summarized version of the problem statement

Compilation Instructions
----------------------------------------------------
1. Open a terminal and navigate to the project directory.
2. Run the following command to compile the program:
       make
   This will automatically compile all source files and generate
   the executable file 'genPlot'.

Execution and Usage Instructions
----------------------------------------------------
1. Ensure that the 'genPlot' executable has been successfully generated.
2. Make sure an input file (e.g., input.txt) exists in the same folder.
3. Run the program using the following command format:
       ./genPlot [MSBCS width] [MSBCS height] [input file] [output file]

   Example:
       ./genPlot 7100 6600 input.txt output.gp

4. After execution, an output file (e.g., output.gp) will be generated
   in the same folder.

5. To generate the Gnuplot visualization (e.g., a .png image), make sure
   Gnuplot is installed, then execute the following command:
       gnuplot output.gp

   This will produce the final visualization based on the generated .gp file.
