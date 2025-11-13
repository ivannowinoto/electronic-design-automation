#include "picRouting.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <queue>
#include <set>
#include <map>

using namespace std;

// Helper function to calculate number of bends in a path
int calculateBends(const vector<Point>& path) {
    if (path.size() < 3) return 0;
    
    int bends = 0;
    for (size_t i = 1; i < path.size() - 1; i++) {
        int dx1 = path[i].x - path[i-1].x;
        int dy1 = path[i].y - path[i-1].y;
        int dx2 = path[i+1].x - path[i].x;
        int dy2 = path[i+1].y - path[i].y;
        
        if (dx1 != dx2 || dy1 != dy2) {
            bends++;
        }
    }
    return bends;
}

// Helper function to calculate Manhattan distance
int manhattanDistance(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Helper function to check if a point is within grid bounds
bool isValidPoint(const Point& p, const Config& config) {
    return p.x >= 0 && p.x < config.gridWidth && p.y >= 0 && p.y < config.gridHeight;
}

// Helper function to check if a point is a start or target point of any net
bool isStartOrTargetPoint(const Point& p, const vector<Net>& nets, int currentNetId) {
    // First check if this point is the current net's own start or target
    for (const Net& net : nets) {
        if (net.id == currentNetId) {
            if ((p.x == net.startX && p.y == net.startY) || 
                (p.x == net.targetX && p.y == net.targetY)) {
                return false;  // Allow using own points
            }
            break;
        }
    }
    
    // Check if this point is any other net's start or target
    for (const Net& net : nets) {
        if (net.id != currentNetId) {  // Only check other nets
            if ((p.x == net.startX && p.y == net.startY) || 
                (p.x == net.targetX && p.y == net.targetY)) {
                return true;  // Prevent using other nets' points
            }
        }
    }
    return false;
}

// Helper function to get valid neighbors of a point
vector<Point> getValidNeighbors(const Point& current, const vector<Net>& nets, 
                              int currentNetId, const Config& config) {
    vector<Point> neighbors;
    vector<Point> directions = {
        Point(1, 0),   // right
        Point(-1, 0),  // left
        Point(0, 1),   // up
        Point(0, -1)   // down
    };

    for (const Point& dir : directions) {
        Point next(current.x + dir.x, current.y + dir.y);
        if (isValidPoint(next, config) && !isStartOrTargetPoint(next, nets, currentNetId)) {
            neighbors.push_back(next);
        }
    }
    return neighbors;
}

// Structure to represent a node in A* search
struct AStarNode {
    vector<Point> path;
    int g_cost;  // Cost from start to current
    int h_cost;  // Estimated cost from current to goal
    int f_cost;  // Total cost (g_cost + h_cost)

    AStarNode(const vector<Point>& p, int g, int h) 
        : path(p), g_cost(g), h_cost(h), f_cost(g + h) {}

    // For priority queue comparison
    bool operator>(const AStarNode& other) const {
        return f_cost > other.f_cost;
    }
};

// Helper function to calculate potential crossing cost for a point
double calculateCrossingCost(const Point& p, const vector<Net>& nets, int currentNetId, const Config& config) {
    double cost = 0.0;
    for (const Net& net : nets) {
        if (net.id == currentNetId) continue;
        
        // Check if this point is in any other net's paths
        for (const vector<Point>& path : net.paths) {
            for (const Point& otherPoint : path) {
                if (p.x == otherPoint.x && p.y == otherPoint.y) {
                    cost += config.crossingLoss;
                    break;
                }
            }
        }
    }
    return cost;
}

vector<Net> routeNets(vector<Net>& nets, const Config& config) {
    for (Net& net : nets) {
        // Clear existing paths
        net.paths.clear();
        
        // Initialize priority queue for A* search
        priority_queue<AStarNode, vector<AStarNode>, greater<AStarNode>> pq;
        
        // Start node
        vector<Point> initialPath = {Point(net.startX, net.startY)};
        int initial_h = manhattanDistance(Point(net.startX, net.startY), 
                                       Point(net.targetX, net.targetY));
        pq.push(AStarNode(initialPath, 0, initial_h));
        
        // Set to keep track of visited points
        set<Point> visited;
        visited.insert(Point(net.startX, net.startY));
        
        // Target point
        Point target(net.targetX, net.targetY);
        
        bool foundPath = false;
        
        while (!pq.empty() && !foundPath) {
            AStarNode current = pq.top();
            pq.pop();
            
            Point currentPoint = current.path.back();
            
            // If we reached the target, this is our optimal path
            if (currentPoint.x == target.x && currentPoint.y == target.y) {
                net.paths.push_back(current.path);
                foundPath = true;
                continue;
            }
            
            // Get valid neighbors
            vector<Point> neighbors = getValidNeighbors(currentPoint, nets, net.id, config);
            
            // Sort neighbors by their potential cost to prioritize better paths
            sort(neighbors.begin(), neighbors.end(), 
                [&](const Point& a, const Point& b) {
                    double costA = manhattanDistance(a, target) + 
                                 calculateCrossingCost(a, nets, net.id, config);
                    double costB = manhattanDistance(b, target) + 
                                 calculateCrossingCost(b, nets, net.id, config);
                    return costA < costB;
                });
            
            // Try each neighbor
            for (const Point& next : neighbors) {
                // Skip if we've already visited this point
                if (visited.find(next) != visited.end()) {
                    continue;
                }
                
                // Calculate new path
                vector<Point> newPath = current.path;
                newPath.push_back(next);
                
                // Calculate costs
                int new_g_cost = current.g_cost + 1;  // Base cost for each step
                int bends = calculateBends(newPath);
                new_g_cost += bends * config.bendingLoss;  // Add cost for bends
                
                // Add crossing cost to g_cost
                new_g_cost += calculateCrossingCost(next, nets, net.id, config);
                
                int new_h_cost = manhattanDistance(next, target);
                
                // Create new node and add to priority queue
                pq.push(AStarNode(newPath, new_g_cost, new_h_cost));
                visited.insert(next);
            }
        }
    }
    
    return nets;
}
