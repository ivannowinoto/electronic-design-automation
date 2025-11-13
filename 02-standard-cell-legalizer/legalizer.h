#ifndef LEGALIZER_H
#define LEGALIZER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

// Struct definition to store necessary values of Row
struct Row {
	string rowName;
	string siteName;
	string orientation;
	int x;
	int y;
	int n;
	int rows;
	int stepX;
	int stepY;
};

// Struct definition for Position (stores x and y coordinate value)
struct Position {
	int x;
	int y;
};

// Struct definition for every component (cells)
struct Component {
	// These values come from input file
	string name;
	string macroName;
	Position currentPos;
	string orientation;
	// These values come from later calculation result
	Position sitePos;
	Position originalPos;
	int displacement;
};


// Function declarations

void getDieDimensions(const string &filename, int &width, int &height);

vector<Row> getRows(const string &filename);

vector<Component> getComponents(const string &filename);

void legalizeCells(vector<Component> &cells, const vector<Row> rows, const int dieWidth, const int dieHeight, const int cellWidth, const int alpha);

void writeOutput(const string& inputFile, const string& outputFile, const vector<Component> cells);

#endif
