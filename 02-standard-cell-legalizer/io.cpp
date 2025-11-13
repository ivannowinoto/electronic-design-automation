#include "legalizer.h"

using namespace std;

// Function to get die width and height
// It assigns value to the dieWidth and dieHeight variables declared in main function
void getDieDimensions(const string& filename, int& width, int& height)
{
	ifstream file(filename);
	string line, keyword;
	char trash;
	int x1, y1, x2, y2;

	if (!file) {
		cerr << "Error: Cannot open input file!" << endl;
		width = height = 0;
		return;
	}

	while (getline(file, line)) {
		istringstream iss(line);
		iss >> keyword;
		if (keyword == "DIEAREA") {
			iss >> trash >> x1 >> y1 >> trash >> trash >> x2 >> y2;
			width = x2 - x1;
			height = y2 - y1;
			return;
		}
	}

	file.close();
	width = height = 0;
}

// Function to read rows information from the input file
vector<Row> getRows(const string &filename)
{
	vector<Row> rows;
	ifstream file(filename);
	string line;

	if (!file) {
		cerr << "Error: Cannot open input file!" << endl;
		return rows;
	}

	while (getline(file, line)) {
		istringstream iss(line);
		string keyword, discard;

		string rowName;
		string siteName;
		string orientation;
		int x;
		int y;
		int n;
		int row;
		int stepX;
		int stepY;

		iss >> keyword;
		if (keyword == "ROW") {
			iss >> rowName >> siteName >> x >> y >> orientation >> discard >> n >> discard >> row >> discard >> stepX >> stepY;
			rows.push_back({ rowName, siteName, orientation, x, y, n, row, stepX, stepY });
		}
		else if (keyword == "COMPONENTS") break;
	}

	file.close();
	return rows;
}

// Function to read cells information from the input file
vector<Component> getComponents(const string& filename)
{
	vector<Component> components;
	ifstream file(filename);
	string line;

	if (!file) {
		cerr << "Error: Cannot open input file!" << endl;
		return components;
	}

	while (getline(file, line)) {
		istringstream iss(line);
		string keyword, discard;
		int n;

		string name;
		string macroName;
		int x;
		int y;
		string orientation;

		iss >> keyword;
		if (keyword == "COMPONENTS") {
			iss >> n;

			for (int i = 0; i < n; i++) {
				getline(file, line);
				iss.clear();
				iss.str(line);
				iss >> discard >> name >> macroName >> discard >> discard >> discard >> x >> y >> discard >> orientation;
				components.push_back({ 
					name, 
					macroName, 
					{x, y}, 
					orientation, 
					{0, 0}, 
					{x, y}, 
					0 
				});
			}
			break;
		}
	}

	file.close();
	return components;
}

// Function to print the output file
void writeOutput(const string &inputFile, const string &outputFile, const vector<Component> cells)
{
	ifstream inFile(inputFile, ios::in);
	ofstream outFile(outputFile, ios::out);
	string line;

	if (!inFile) {
		cerr << "Error: Cannot open input file!" << endl;
		return;
	}

	if (!outFile) {
		cerr << "Error: Cannot open output file!" << endl;
		return;
	}

	while (getline(inFile, line)) {
		istringstream iss(line);
		string keyword;
		int n;

		iss >> keyword;
		if (keyword == "COMPONENTS") {
			iss >> n;
			outFile << "COMPONENTS " << n << " ;" << endl;
			for (const auto& c : cells) {
				outFile << "- " << c.name << " " << c.macroName << " + PLACED ( " << c.currentPos.x << " " << c.currentPos.y << " ) " << c.orientation << " ;" << endl;
			}
			outFile << "END COMPONENTS" << endl << endl << "END DESIGN";
			break;
		}
		else {
			outFile << line << endl;
		}
	}

	inFile.close();
	outFile.close();
	return;
}
	


