#include <iostream>
#include <string>
#include "picRouting.h"

using namespace std;

int main(int argc, char*argv[])
{
    if (argc != 3) {
      cout << "Usage: [executable file name] [input file name] [output file name]" << endl;
      return 1;
    }
    
    string inputFileName = argv[1];
    string outputFileName = argv[2];
    Config config;
    vector<Net> nets;
    
    // Read input
    readConfig(inputFileName, config);
    readNets(inputFileName, nets, config.numNets);

    // Route nets
    nets = routeNets(nets, config);

    // Write output to file
    writeRoutes(outputFileName, nets, config);

    // Calculate and display loss information
    double totalLength;
    int totalBends;
    int totalCrossings;
    double totalLoss;
    calculateTotalSystemLoss(nets, config, totalLength, totalBends, totalCrossings, totalLoss);

    cout << "Input file: " << inputFileName << endl;
    cout << "Output file: " << outputFileName << endl;
    cout << "\nLoss Information:" << endl;
    cout << "Total System Loss: " << totalLoss << endl;
    cout << "Breakdown:" << endl;
    cout << "- Total Length: " << totalLength << " units" << endl;
    cout << "- Total Bends: " << totalBends << endl;
    cout << "- Total Crossings: " << totalCrossings << endl;
    cout << "- Propagation Loss: " << (totalLength * config.propagationLoss) << endl;
    cout << "- Bending Loss: " << (totalBends * config.bendingLoss) << endl;
    cout << "- Crossing Loss: " << (totalCrossings * config.crossingLoss) << endl;

    return 0;
}


