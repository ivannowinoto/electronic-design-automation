#include "legalizer.h"

using namespace std;

// Function to sort all cells in the same row according to their x-position
void sortByPosition(vector<Component>& cells) 
{
	sort(cells.begin(), cells.end(), [](const Component& a, const Component& b) {
		return a.currentPos.x < b.currentPos.x;
		});
}

// Functions to place all cells into a valid row and set the orientation of each cell according to rows' orientation
void placeCellsY(vector<Component>& cells, const vector<int> yPoints, const int dieHeight, const vector<Row> rows)
{
	int rowHeight = yPoints[1] - yPoints[0]; // Assume each row has the same height

	for (auto& c : cells) {
		c.sitePos.y = c.currentPos.y / rowHeight;
		if (c.currentPos.y >= yPoints.back()) {	// If cell's y-position exceeds last row's y-position (too high)
			c.currentPos.y = yPoints.back();
			c.orientation = rows.back().orientation;
		}
		else if (c.currentPos.y <= 0) {			// If cell's y-position is negative
			c.currentPos.y = yPoints[0];
			c.orientation = rows[0].orientation;
		}
		else {
			if (c.currentPos.y - yPoints[c.sitePos.y] > rowHeight / 2) {	// If cell is closer to the next row (more than 50% into it)
				c.currentPos.y = yPoints[c.sitePos.y + 1];					// Set cell's y-position to the next row
				c.orientation = rows[c.sitePos.y + 1].orientation;
			}
			else {
				c.currentPos.y = yPoints[c.sitePos.y];						// Set cell's y-position to the current row
				c.orientation = rows[c.sitePos.y].orientation;
			}
		}
	}
}

void placeCellsX(vector<Component>& cells, const vector<int> xPoints, const int dieWidth, const int cellWidth, const int siteWidth)
{
	for (auto& c : cells) {
		if (c.currentPos.x >= xPoints[xPoints.size() - cellWidth]) {	// If cell's x-position exceeds the boundary
			c.currentPos.x = xPoints[xPoints.size() - cellWidth];
		}
		else if (c.currentPos.x < 0) {		// If cell's x-position is negative
			c.currentPos.x = xPoints[0];
		}
		else {
			c.sitePos.x = c.currentPos.x / siteWidth;
			// If cell is closer to the next site, set the cell's x-position to the next site, else set to current site
			c.currentPos.x = (c.currentPos.x - xPoints[c.sitePos.x] > siteWidth / 2) ? xPoints[c.sitePos.x + 1] : xPoints[c.sitePos.x];
		}
	}
}

// Function to group cells according to their rows in a 2D vector
vector<vector<Component>> groupCells(const vector<Component> cells, const vector<int> yPoints, const int dieWidth, const int totalCellWidth)
{
	vector<vector<Component>> groupedCells;
	
	// Iterate for every row
	for (int i = 0; i < yPoints.size(); i++) {
		vector<Component> sameRowCells;
		for (auto& c : cells) {
			if (c.currentPos.y == yPoints[i]) {	// If there are cells in the same row, push to sameRowCells
				sameRowCells.push_back(c);
			}
		}
		 //Calculate if die width can fit all cells in the row
		int index = 0;
		while (sameRowCells.size() * totalCellWidth > dieWidth) {
			if (i == yPoints.size() - 1) break;
			groupedCells[i + 1].push_back(sameRowCells[index]);	// If not, then move cells to next row until it fits
			sameRowCells.erase(sameRowCells.begin() + index);
			index++;
		}

		groupedCells.push_back(sameRowCells);	// Push sameRowCells to groupedCells
		sameRowCells.clear();	// Empty the vector
	}

	return groupedCells;
}

// Function to legalize every cells in the same row so that no cell overlaps each other
void legalizePerRow(vector<vector<Component>>& groupedCells, const int totalCellWidth)
{	
	for (int i = 0; i < groupedCells.size(); i++) {		// Iterate for every row
		if (groupedCells[i].size() == 0) continue;		// If there are no cells in the current row, continue to the next row
		int currentX = groupedCells[i][0].currentPos.x;	// Set the leftmost valid x-position
		for (auto& c : groupedCells[i]) {
			if (c.currentPos.x < currentX) {			// If a cell's x-position is less than leftmost valid x-position (overlapping)
				c.currentPos.x = currentX;				// Set the cell's x-position to the leftmost valid position
			}
			currentX = c.currentPos.x + totalCellWidth;					// Increment the leftmost valid x-position 
		}
	}
}

// Function to check if the cells are out of the die area
void checkBounds(vector<vector<Component>>& groupedCells, const int dieWidth, const int totalCellWidth)
{
	for (int i = 0; i < groupedCells.size(); i++) {		// Iterate for every row
		if (groupedCells[i].size() == 0) continue;		// If there are no cells in the current row, continue to the next row
		int lastValidX = dieWidth - totalCellWidth;		// Set the rightmost valid x-position
		for (auto it = groupedCells[i].rbegin(); it != groupedCells[i].rend(); ++it) {
			auto& c = *it;
			if (c.currentPos.x >= lastValidX) {		// If a cell's x-position is more than rightmost valid x-position (out of die area)
				c.currentPos.x = lastValidX;			// Set the cell's x-position to the rightmost valid position
			}
			lastValidX -= totalCellWidth;				// Decrement the rightmost valid x-position
		}
	}
}

// Function to give value to each cells' displacement (initially 0)
void calculateCellDisplacement(vector<vector<Component>>& groupedCells)
{
	for (int i = 0; i < groupedCells.size(); i++) {
		if (groupedCells[i].size() == 0) continue;
		for (auto& c : groupedCells[i]) {
			// The displacement is calculated using Manhattan distance, which is the sum of the absolute difference of original and moved positions of a cell in both x and y directions
			c.displacement = abs(c.currentPos.x - c.originalPos.x) + abs(c.currentPos.y - c.originalPos.y);
		}
	}
}

// Function to assign the values of groupedCells into cells
void assignValues(vector<Component>& cells, const vector<vector<Component>> groupedCells)
{
	unordered_map <string, Component> tempCells;	// Use unordered map to assign the values

	for (const auto row : groupedCells) {
		for (const auto c : row) {
			tempCells[c.name] = c;
		}
	}

	for (auto& c : cells) {
		if (tempCells.find(c.name) != tempCells.end()) {	// Find the exact same name of a component, and assign all the other values 
			c = tempCells[c.name];
		}
	}
}

// Function to calculate the cost of the whole arrangement
int calculateCost(const vector<vector<Component>> groupedCells, const int alpha)
{
	int sum = 0, n = 0;
	int maxDisplacement = 0, avgDisplacement = 0;
	int cost = 0;

	for (int i = 0; i < groupedCells.size(); i++) {
		if (groupedCells[i].size() == 0) continue;	// If there are no cells in the current row, continue to the next row
		for (auto c : groupedCells[i]) {
			// Find the maximum displacement of a cell in the whole arrangement
			//maxDisplacement = (c.displacement > maxDisplacement) ? c.displacement : maxDisplacement;
			if (c.displacement > maxDisplacement) {
				maxDisplacement = c.displacement;
			}
			sum += c.displacement;
			n++;
		}
	}
	// Calculate average displacement and cost

	avgDisplacement = sum / n;
	cost = avgDisplacement + alpha * maxDisplacement;

	return cost;
}

// The function below (tryAlternatePosition) is the function to try every possible position on every cells in a particular row
// It works by moving each cell to every possible non-overlapping positions, then calculate the cost of the whole arrangement
// Then, it will choose the arrangement with the lowest cost as its final result
// However, the legalizePerRow and checkBounds function always produces the lowest cost arrangement, so there is no need to use this function again
// The second problem of this function is that it only works on the case 1~4 files, on the super files it takes too long to run
// Maybe TA can try using this function if you want to compare the cost of each arrangement

bool overlap(const int x1, const int x2, const int totalCellWidth)
{
	return x1 + totalCellWidth > x2;
}

void tryAlternatePosition(vector<vector<Component>>& groupedCells, const int totalCellWidth, const int dieWidth, const int alpha)
{
	int minCost = calculateCost(groupedCells, alpha);
	int newCost = 0;

	vector<int> allXPoints;
	for (int i = 0; i < dieWidth / totalCellWidth; i++) {
		allXPoints.push_back(i);
		allXPoints.push_back(-i);
	}

	// Iterate over each row group.
	for (int i = 0; i < groupedCells.size(); i++) {
		if (groupedCells[i].empty())
			continue;  // Skip empty rows

		// Iterate over each cell in this row.
		for (int j = 0; j < groupedCells[i].size(); j++) {

			// Try both right (+totalCellWidth) and left (-totalCellWidth) moves.
			for (int direction : allXPoints) {
				// Save the original x position.
				int originalX = groupedCells[i][j].currentPos.x;

				// Move the cell by totalCellWidth in the current direction.
				groupedCells[i][j].currentPos.x += direction * totalCellWidth;
				if (groupedCells[i][j].currentPos.x < 0 or groupedCells[i][j].currentPos.x > dieWidth - totalCellWidth) { // If out of bounds
					groupedCells[i][j].currentPos.x = originalX;
					break;
				}

				// Check for overlaps with adjacent cells.
				bool validMove = true;
				if (j > 0) { // Check left neighbor.
					if (overlap(groupedCells[i][j - 1].currentPos.x, groupedCells[i][j].currentPos.x, totalCellWidth)) {
						validMove = false;
					}
				}
				if (j < groupedCells[i].size() - 1) { // Check right neighbor.
					if (overlap(groupedCells[i][j].currentPos.x, groupedCells[i][j + 1].currentPos.x, totalCellWidth)) {
						validMove = false;
					}
				}

				// Revert and break out of the loop if the move is invalid (is overlapping)
				if (!validMove) {
					groupedCells[i][j].currentPos.x = originalX;
					break;
				}

				// The code below this is when the move is valid
				calculateCellDisplacement(groupedCells);	// Calculate the cell displacements again
				newCost = calculateCost(groupedCells, alpha);	// 

				// Output the newCost in terminal
				cout << "Moved x-position of " << groupedCells[i][j].name << " " << groupedCells[i][j].macroName << " to " << groupedCells[i][j].currentPos.x << endl;
				cout << "New cost: " << newCost << endl << endl;			
 
				if (newCost < minCost) {
					minCost = newCost;
				}
				else {
					groupedCells[i][j].currentPos.x = originalX;
				}
			}
		}
	}
}

void legalizeCells(vector<Component>& cells, const vector<Row> rows, const int dieWidth, const int dieHeight, const int cellWidth, const int alpha)
{
	vector<int> yPoints, xPoints;

	// Set initial values
	int sites = rows[0].n;
	int siteWidth = rows[0].stepX;

	// Get all rows position
	for (auto r : rows) {
		yPoints.push_back(r.y);
		//cout << "Y: " << r.y << endl;
	}

	// Get all sites in x-position
	for (int i = 0; i < sites; i++) {
		xPoints.push_back(i * siteWidth);
	}

	int totalCellWidth = cellWidth * siteWidth;

	// Place the cells to the closest rows and sites from their original position (the result might still be overlapping)
	placeCellsY(cells, yPoints, dieHeight, rows);
	placeCellsX(cells, xPoints, dieWidth, cellWidth, siteWidth);

	// Group cells according to rows (1 row = 1 group of cells)
	vector<vector<Component>> groupedCells = groupCells(cells, yPoints, dieWidth, totalCellWidth);

	// Sort grouped cells (sort in ascending order per row)
	for (int i = 0; i < groupedCells.size(); i++)
		sortByPosition(groupedCells[i]);

	// Place cells so there are no overlapping
	legalizePerRow(groupedCells, totalCellWidth);

	// Check if the last cell in a row is out of die area
	// If yes, check from the last cell and move until no overlap
	checkBounds(groupedCells, dieWidth, totalCellWidth);

	// After moving all the cells into their valid positions, finally calculate the displacement of each cell
	calculateCellDisplacement(groupedCells);

	// Until now, all the values are modified in the groupedCells 2D vector
	// Now, it is time to assign all the values into the original vector of components
	assignValues(cells, groupedCells);

	// TA can call this function if want to try checking all the cost of every possible cell arrangement
	// Note: this function still cannot be used on super files
	// tryAlternatePosition(groupedCells, totalCellWidth, dieWidth, alpha);

	cout << "Legalizing cells total cost: " << calculateCost(groupedCells, alpha) << endl << endl;

} 
