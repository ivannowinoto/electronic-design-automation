#include "genPlot.h"
#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

int main(int argc, char** argv) {

    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <MSBCS width> <MSBCS height> <input file name> <output file name>" << endl;
        return 1;
    }

    int MSBCSwidth = stoi(argv[1]);
    int MSBCSheight = stoi(argv[2]);
    
    string inputFileName = argv[3];
    string outputFileName = argv[4];

    int width = getDieWidth(inputFileName);
    int height = getDieHeight(inputFileName);

    vector<Transistor> transistors = getComponents(inputFileName);
    vector<Metal> metals = getSpecialnets(inputFileName);

    if (!transistors.empty()) {
        writeOutputGnuplotFile(transistors, metals, outputFileName, width, height, MSBCSwidth, MSBCSheight);
        cout << "Gnuplot file generated: " << outputFileName << endl;
    }
    else {
        cerr << "No transistors found in DEF file" << endl;
    }

    return 0;
}

