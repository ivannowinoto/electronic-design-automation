#include "genPlot.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Read the die area from the file: Read width and height

// Read die width
int getDieWidth(const string& filename)
{
	int width = 0;
	ifstream file(filename);
	string line, keyword;
	char trash;
	int x1, y1, x2, y2;

	if (!file) {
		cerr << "Error: Could not open file!" << endl;
		return width;
	}

	while (getline(file, line)) {
		istringstream iss(line);

		iss >> keyword;
		if (keyword == "DIEAREA") {
			iss >> trash >> x1 >> y1 >> trash >> trash >> x2 >> y2;
			break;
		}
	}
	width = x2 - x1;
	
	return width;
}

// Read die height 
int getDieHeight(const string& filename)
{
	int height = 0;
	ifstream file(filename);
	string line, keyword;
	char trash;
	int x1, y1, x2, y2;

	if (!file) {
		cerr << "Error: Could not open file!" << endl;
		return height;
	}

	while (getline(file, line)) {
		istringstream iss(line);

		iss >> keyword;
		if (keyword == "DIEAREA") {
			iss >> trash >> x1 >> y1 >> trash >> trash >> x2 >> y2;
			break;
		}
	}
	height = y2 - y1;

	return height;
}

// Read all transistor values and store using vector
vector<Transistor> getComponents(const string& filename) 
{
	vector<Transistor> transistors;
	ifstream file(filename);
	string line;

	if (!file) {
		cerr << "Error: Could not open file!" << endl;
		return transistors;
	}

	while (getline(file, line)) {
		istringstream iss(line);
		string keyword, trash, name;
		int n, x, y;

		iss >> keyword;
		if (keyword == "COMPONENTS") {
			iss >> n;
			
			for (int i = 0; i < n; i++) {
				getline(file, line);
				iss.clear();
				iss.str(line);
				iss >> trash >> name;
				
				getline(file, line);
				iss.clear();
				iss.str(line);
				iss >> trash >> trash >> trash >> x >> y;
				transistors.push_back({ name, x, y });
			}
			break;
		}
	}

	file.close();
	return transistors;
}

// Read all metal values and store using vector
vector<Metal> getSpecialnets(const string& filename)
{
	vector<Metal> metals;
	ifstream file(filename);
	string line;

	if (!file) {
		cerr << "Error: Could not open file!" << endl;
		return metals;
	}

	while (getline(file, line)) {
		istringstream iss(line);
		string keyword, trash, name, type;
		int n, width, x1, y1, x2, y2;
		string x2str, y2str;

		iss >> keyword;
		if (keyword == "SPECIALNETS") {
			iss >> n;

			for (int i = 0; i < n; i++) {
				getline(file, line);
				iss.clear();
				iss.str(line);
				iss >> trash >> name;

				getline(file, line);
				iss.clear();
				iss.str(line);
				iss >> trash >> trash >> type >> width >> trash >> x1 >> y1 >> trash >> trash >> x2str >> y2str;
				if (x2str == "*") { x2 = x1; }
				else {
					stringstream ss(x2str);
					ss >> x2;
				}
				if (y2str == "*") { y2 = y1; }
				else {
					stringstream ss(y2str);
					ss >> y2;
				}
					
				metals.push_back({ name, type, x1, y1, x2, y2, width });

			}
			break;
		}
	}

	file.close();
	return metals;
}

// Writing the Gnuplot syntax in output file
void writeOutputGnuplotFile(const vector<Transistor>& transistors, const vector<Metal>& metals, const string& outputFileName, const int& dieWidth, const int& dieHeight, const int& MSBCSwidth, const int& MSBCSheight) 
{
	ofstream file(outputFileName);

	if (!file) {
		cerr << "Error: Could not create output file!" << endl;
		return;
	}

	file << "reset" << endl;

	file << "set terminal png size 2048,1536" << endl;
	file << "set output 'output.png'" << endl;

    file << "set title 'Result'" << endl;
    file << "set xlabel 'X-axis'" << endl;
    file << "set ylabel 'Y-axis'" << endl;

	int i = 1;
	for (const auto& m : metals) {
		int botLeftX, botLeftY, topRightX, topRightY;
		string metalLabel;

		for (char c : m.name) {
			if (c == '_')
				metalLabel += "\\_"; // Escape underscore
			else
				metalLabel += c;
		}

		if (m.type == "ME3") {
			botLeftX = m.x1 - (m.width / 2);
			if (botLeftX < 0) botLeftX = 0;
			botLeftY = m.y1;
			topRightX = m.x2 + (m.width / 2);
			topRightY = m.y2;

			file << "set object " << i << " rect from " << botLeftX << "," << botLeftY << " to " << topRightX << "," << topRightY << " fc 'red' fs transparent solid border linecolor 'red' lw 2" << endl;
			file << "set label '" << metalLabel << "' at " << m.x1 << "," << botLeftY << " rotate by 90 font 'Arial,8'" << endl;
		}
		else if (m.type == "ME4") {
			botLeftX = m.x1;
			botLeftY = m.y1 - (m.width / 2);
			if (botLeftY < 0) botLeftY = 0;
			topRightX = m.x2;
			topRightY = m.y2 + (m.width / 2);
			file << "set object " << i << " rect from " << botLeftX << "," << botLeftY << " to " << topRightX << "," << topRightY << " fc 'blue' fs transparent solid border linecolor 'blue' lw 2" << endl;
			file << "set label '" << metalLabel << "' at " << botLeftX << "," << m.y1 << " left font 'Arial,10'" << endl;
		}
		botLeftX = 0;
		botLeftY = 0;
		topRightX = 0;
		topRightY = 0;
		i++;
	}

	for (const auto& t : transistors) {
		int x1, x2, y1, y2;
		x1 = t.x;
		y1 = t.y;
		x2 = t.x + MSBCSwidth;
		y2 = t.y + MSBCSheight;
		string transistorLabel;

		for (char c : t.name) {
			if (c == '_')
				transistorLabel += "\\_"; // Escape underscore
			else
				transistorLabel += c;
		}

		file << "set object " << i << " rect from " << x1 << "," << y1 << " to " << x2 << "," << y2 << " fc 'yellow' fs transparent solid border linecolor 'yellow' lw 2" << endl;
		file << "set label '" << transistorLabel << "' at " << (x1 + x2) / 2 << "," << (y1 + y2) / 2 << " center font 'Arial,10'" << endl;

		x1 = 0;
		x2 = 0;
		y1 = 0;
		y2 = 0;
		i++;
	}

    file << "set object " << i << " rect from 0,0 to " << dieWidth << "," << dieHeight << " fs empty linecolor '#C080FF' lw 3" << endl;
    file << "set xtics 10000" << endl;
    file << "set ytics 10000" << endl;
    file << "set size square" << endl;
    file << "set grid" << endl;
    file << "plot [-5000:" << dieWidth + 5000 << "][-5000:" << dieHeight + 5000 << "] 0" << endl;
	file << "replot" << endl;

	file.close();
}


