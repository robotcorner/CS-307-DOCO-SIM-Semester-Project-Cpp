#pragma once
#include <vector>
#include "GridSize.h"
#include "Cell.h"

// Is a grid of cell objects in the form of a matrix

class CellGrid
{
protected:
	GridSize my_grid_size;		// holds the details about the CellGrid
	std::vector<std::vector<char> > char_matrix;		// holds matrix of the characters to represent
	std::vector<std::pair<int, int> > temp_adjoined_cells; // holds vector of adjoined cells for a given position

public:
	std::vector<std::vector<Cell> > cell_matrix;		// holds the matrix of cell objects
	CellGrid(int h, int w);	// creates the gridShape to the specified heightand width, then populates the cell_matrix with cell_objects initialized to each position.
	~CellGrid(); // de-allocates memory for CellGrid object
	
	void setCharMatrix(void);  // Set the char_matrix to their appropriate characters based on the status of the cells.
	std::vector<std::pair<int, int> > findAdjoinedCells(int x, int y); // using the xand y position provided in conjunction with its data on the cell matrix, finds the cells within one space of it(N, E, S, W, NE, SE, SW, NW).
	std::vector<std::pair<int, int> > findAdjoinedOccupiedCells();
	std::vector<std::pair<int, int> > findAdjoinedCellsFood(); // checks each of the temp_adjoining_cells and returns the matrix of cells that contain food.Using the temp variable eliminates some error checking.
	std::vector<std::vector<Cell> > getMatrix(void); // returns the cell_matrix private variable
	std::vector<std::vector<char> > getCharMatrix(); // returns the char_matrix private variable
	void printCharMatrix(); // returns the character matrix in printed to the console based off of the char_matrix class property.
};

