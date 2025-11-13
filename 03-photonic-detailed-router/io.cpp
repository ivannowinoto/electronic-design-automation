#include "picRouting.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <queue>
#include <set>
#include <map>

using namespace std;

void readConfig(const string& filename, Config& config) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return;
    }

    string line;
    string keyword;
    
    // Read grid dimensions
    getline(file, line);
    istringstream iss(line);
    iss >> keyword >> config.gridWidth >> config.gridHeight;

    // Read propagation loss
    getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> keyword >> keyword >> config.propagationLoss;

    // Read crossing loss
    getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> keyword >> keyword >> config.crossingLoss;

    // Read bending loss
    getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> keyword >> keyword >> config.bendingLoss;

    // Read number of nets
    getline(file, line);
    iss.clear();
    iss.str(line);
    iss >> keyword >> keyword >> config.numNets;

    file.close();
}

void readNets(const string& filename, vector<Net>& nets, int numNets) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return;
    }

    string line;
    // Skip the first 5 lines (config information)
    for (int i = 0; i < 5; i++) {
        getline(file, line);
    }

    // Read net information
    for (int i = 0; i < numNets; i++) {
        if (getline(file, line)) {
            istringstream iss(line);
            Net net;
            iss >> net.id >> net.startX >> net.startY >> net.targetX >> net.targetY;
            net.paths.clear();  // Initialize empty paths
            nets.push_back(net);
        }
    }

    file.close();
}

// Helper function to calculate total waveguide loss for all paths
void calculateTotalSystemLoss(const vector<Net>& nets, const Config& config, 
                            double& totalLength, int& totalBends, int& totalCrossings, double& totalLoss) {
    totalLength = 0;
    totalBends = 0;
    totalCrossings = 0;
    
    // First pass: calculate total length and bends
    for (const Net& net : nets) {
        for (const vector<Point>& path : net.paths) {
            // Add path length (number of segments)
            totalLength += path.size() - 1;
            
            // Count bends
            for (size_t i = 1; i < path.size() - 1; i++) {
                int dx1 = path[i].x - path[i-1].x;
                int dy1 = path[i].y - path[i-1].y;
                int dx2 = path[i+1].x - path[i].x;
                int dy2 = path[i+1].y - path[i].y;
                
                if (dx1 != dx2 || dy1 != dy2) {
                    totalBends++;
                }
            }
        }
    }
    
    // Second pass: count crossings
    map<Point, int> pointCount;
    for (const Net& net : nets) {
        for (const vector<Point>& path : net.paths) {
            for (const Point& p : path) {
                pointCount[p]++;
            }
        }
    }
    
    // Count points where multiple paths cross
    for (const auto& pair : pointCount) {
        if (pair.second > 1) {
            totalCrossings++;
        }
    }
    
    // Calculate total loss
    totalLoss = (totalLength * config.propagationLoss) + 
                (totalBends * config.bendingLoss) + 
                (totalCrossings * config.crossingLoss);
}

void writeRoutes(const string& filename, const vector<Net>& nets, const Config& /*config*/) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output file: " << filename << endl;
        return;
    }

    for (const Net& net : nets) {
        if (!net.paths.empty()) {
            // Write net ID and route length (number of segments)
            outFile << net.id << " " << (net.paths[0].size() - 1) << endl;
            
            // Write each segment of the path
            const vector<Point>& path = net.paths[0];
            for (size_t i = 0; i < path.size() - 1; i++) {
                outFile << path[i].x << " " << path[i].y << " "
                       << path[i + 1].x << " " << path[i + 1].y << endl;
            }
        }
    }

    outFile.close();
}


