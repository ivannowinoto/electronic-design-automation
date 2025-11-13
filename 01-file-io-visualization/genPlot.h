#ifndef GENPLOT_H
#define GENPLOT_H

#include <string>
#include <vector>

using namespace std;

// Define two structs for transistors and metals

struct Transistor {
	string name;
	int x, y;
};

struct Metal {
	string name, type;
	int x1, y1, x2, y2, width;
};


// Defining all functions

int getDieWidth(const string& filename);

int getDieHeight(const string& filename);

vector<Transistor> getComponents(const string& filename);

vector<Metal> getSpecialnets(const string& filename);

void writeOutputGnuplotFile(const vector<Transistor>& transistors, const vector<Metal>& metals, const string& outputFileName, const int& dieWidth, const int& dieHeight, const int& MSBCSwidth, const int& MSBCSheight);

#endif
