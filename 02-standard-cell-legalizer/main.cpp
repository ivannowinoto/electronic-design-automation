#include "legalizer.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char*argv[])
{
    if (argc != 5) {
        cout << "Usage: ./legalizer [cell width (in terms of sites)] [alpha] [input file name] [output file name]" << endl;
        return 1;
    }

    int cellWidth = stoi(argv[1]);         // Cell width in number of sites
    int alpha = stoi(argv[2]);             // Weight factor (likely for optimization objective)
    string inputFile = argv[3];            // Input DEF file
    string outputFile = argv[4];           // Output file name

    int dieWidth, dieHeight;

    vector<Row> rows = getRows(inputFile);
    vector<Component> cells = getComponents(inputFile);

    cout << "------------Succesfully read input file!------------\n\n";

    getDieDimensions(inputFile, dieWidth, dieHeight);

    cout << "Legalizing cells..." << endl << endl;
    
    legalizeCells(cells, rows, dieWidth, dieHeight, cellWidth, alpha);
    
    cout << "------------Succesfully legalized cells!------------\n\n";

    writeOutput(inputFile, outputFile, cells);

    cout << "------------Output file " << outputFile << " created------------\n\n";

    return 0;
}

