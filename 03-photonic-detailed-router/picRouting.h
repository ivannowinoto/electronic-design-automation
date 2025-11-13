#ifndef PIC_ROUTING_H
#define PIC_ROUTING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// Structure to store configuration information
struct Config {
    int gridWidth;
    int gridHeight;
    double propagationLoss;
    double crossingLoss;
    double bendingLoss;
    int numNets;
};

// Structure to store a point in the grid
struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

// Structure to store net information
struct Net {
    int id;
    int startX;
    int startY;
    int targetX;
    int targetY;
    std::vector<std::vector<Point>> paths;  // Stores multiple possible paths from start to target
};

// Function declarations
void readConfig(const std::string& filename, Config& config);
void readNets(const std::string& filename, std::vector<Net>& nets, int numNets);
void writeRoutes(const std::string& filename, const std::vector<Net>& nets, const Config& /*config*/);
std::vector<Net> routeNets(std::vector<Net>& nets, const Config& config);
void calculateTotalSystemLoss(const std::vector<Net>& nets, const Config& config, 
                            double& totalLength, int& totalBends, int& totalCrossings, double& totalLoss);

// Helper function declarations
int calculateBends(const std::vector<Point>& path);

#endif // PIC_ROUTING_H
