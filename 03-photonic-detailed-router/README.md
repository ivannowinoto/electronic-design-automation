# Programming Assignment #3: Detailed Routing for Photonic Integrated Circuits (PICs)

A C++ implementation of a routing algorithm for Photonic Integrated Circuits (PIC).

## Overview

This project implements routing algorithms for photonic integrated circuits, optimizing signal paths while minimizing losses.

## Technical Specifications

- **Language**: C++
- **Compiler**: Linux GNU g++
- **Platform**: Linux

## Project Structure

```
b11107035-p3/
├── main.cpp          # Main source code
├── io.cpp            # Input/output functions
├── picRouting.cpp    # Core routing algorithm implementations
├── picRouting.h      # Header file with data structures
├── Makefile          # Build configuration
├── README.md         # This file
├── pa3.txt           # Summarized problem statement
├── pa3_resources/    # Directory containing test input files
└── report.pdf        # Documentation of data structures and algorithms
```

## Getting Started

### Prerequisites

- Linux operating system
- GNU g++ compiler
- Make utility

### Compilation

1. Navigate to the project directory:
   ```bash
   cd b11107035-p3/
   ```

2. Compile the project:
   ```bash
   make
   ```

This will generate the `picRouting` executable file.

### Usage

Run the program with the following command:

```bash
./picRouting [input_file] [output_file]
```

**Example:**
```bash
./picRouting pic5x5.in output.txt
```

### Input/Output

- **Input**: Place your input file (e.g., `pic5x5.in`) in the same directory as the executable
- **Output**: 
  - Terminal output displaying loss information
  - Generated output file (`.txt`) in the same directory

## Notes

- Ensure the input file exists in the project directory before running
- The program will create the output file automatically
- Check the `report.docx` for detailed information about the algorithms and data structures used