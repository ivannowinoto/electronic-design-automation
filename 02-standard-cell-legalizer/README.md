# Programming Assignment 2: Single-Row-Height Cell Legalization

## Overview

This project implements a cell legalization algorithm for single-row-height cells in VLSI physical design. The program reads a design file, applies legalization constraints, and outputs the optimized placement results.

## Requirements

- **Language:** C++
- **Platform:** Linux
- **Compiler:** GNU g++

## Project Structure

```
.
├── main.cpp          # Main program entry point
├── io.cpp            # Input/output operations handler
├── legalizer.cpp     # Cell legalization implementation
├── legalizer.h       # Data structures and function declarations
├── Makefile          # Build automation
├── README.md         # Project documentation
├── report.docx       # Detailed algorithm and data structure report
├── pa2_testcases/    # Directory containing test input files
└── pa2.txt           # Problem statement summary
```

## Building the Project

### Compilation

Navigate to the project directory and run:

```bash
make
```

This will compile all source files and generate the executable `legalizer`.

### Cleaning Build Files

To remove compiled objects and executables:

```bash
make clean
```

## Usage

### Command Syntax

```bash
./legalizer [cell_width] [alpha] [input_file] [output_file]
```

### Parameters

| Parameter | Description |
|-----------|-------------|
| `cell_width` | Cell width measured in number of sites |
| `alpha` | Algorithm parameter (weighting factor) |
| `input_file` | Input DEF file (e.g., `case1.def`) |
| `output_file` | Output file for legalized results |

### Example

```bash
./legalizer 2 2 case1.def output.txt
```

This command:
- Uses a cell width of 2 sites
- Sets alpha parameter to 2
- Reads from `case1.def`
- Writes results to `output.txt`

## Input/Output Format

### Input
The program accepts DEF (Design Exchange Format) files containing initial cell placements.

### Output
The output file contains legalized placement coordinates in the same format as the input file, with cells repositioned to satisfy all legalization constraints.