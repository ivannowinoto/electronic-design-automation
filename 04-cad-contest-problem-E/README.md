# CAD Contest – Problem E: RTL Re-connection

A C++ implementation of an automated RTL reconnection tool for updating sub-module interfaces in Verilog designs.
This problem originated from CAD Contest 2025 held by ICCAD.

## Overview

This project implements an automatic reconnection tool for RTL (Register Transfer Level) designs. When sub-modules are updated with modified signal names or interface conventions, this tool generates a new top module that maintains equivalent functionality while connecting to the updated sub-modules. The tool focuses exclusively on combinational logic and preserves all top-level I/O signal names.

## Technical Specifications

- **Language**: C or C++
- **Compiler**: Linux GNU g++ (C++ standard)
- **Platform**: Linux
- **Standard**: IEEE 1364-2005 Verilog
- **Time Constraint**: 2 hours per testcase (terminated if exceeded)

## Project Structure

```
b11107035-p3/
├── main.cpp          # Main program entry point
├── io.cpp            # Input/output and Verilog file parsing
├── RTL.cpp           # Core reconnection algorithm implementations
├── RTL.h             # Header file with data structures and declarations
├── Makefile          # Build configuration
├── README.md         # This file
├── readme.txt        # Plain text version of instructions
├── report.docx       # Algorithm documentation
└── test/             # Directory containing test input files
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

This will generate the executable file.

### Usage

Run the program with the following command:

```bash
./<executable> top_module.v sub_module.v new_sub_module.v update_information new_top_module.v
```

**Example:**

```bash
./rtl top_module.v sub_module.v new_sub_module.v update_information new_top_module.v
```

### Input Files

1. **top_module.v**: Original top module containing interface connections between top and sub-modules
2. **sub_module.v**: Original sub-module definitions (one or more modules)
3. **new_sub_module.v**: Updated sub-module definitions to replace originals
4. **update_information**: Rename mapping file with two possible formats:
   - Format 1: `<signal A> is renamed.`
   - Format 2: `<signal B> is renamed to <signal C>.`

### Output File

**new_top_module.v**: Generated top module that:
- Preserves all original top module I/O signal names
- Updates sub-module port connections according to rename rules
- Maintains equivalent functionality to the original design
- Contains only port-level reconnections (no logic modifications)

## Algorithm Overview

The tool performs the following operations:
1. Parses original and new Verilog module definitions
2. Extracts signal rename mappings from update_information
3. Identifies port connections requiring updates
4. Generates new top module with updated port mappings
5. Validates equivalent functionality preservation

Key constraints:
- Old and new sub-modules have identical port counts and bit-widths
- Only signals listed in update_information are modified
- No combinational logic modifications are performed
- Format 2 mappings can be directly applied for signal replacement

## Verification

A checker tool is provided to verify correctness:

```bash
./checker <testcase> <input_match>
```

The `input_match` file contains complete mappings of all renamed signals.

## Scoring Criteria

- **Points**: 1 point per testcase
- **Multiple Sub-modules**: Each contributes 1/n to the score
- **Tie-breaker**: Shorter total runtime
- **Compliance**: Must follow IEEE 1364-2005 Verilog standard
- **Timeout**: Programs terminated after 2 hours, scored on current output

## Test Cases

- 5 public testcases
- 5 hidden testcases
- All testcases weighted equally

## Notes

- Only port-level reconnection is required; do not modify internal logic
- All top-level I/O signal names must remain unchanged
- Signals not mentioned in update_information retain their original names
- Output must be valid Verilog conforming to IEEE 1364-2005
- Ensure the generated new_top_module.v maintains functional equivalence
- See `report.docx` for detailed algorithm and data structure explanations