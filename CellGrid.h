#pragma once
#include <vector>
#include "GridSize.h"
#include "Cell.h"

// Is a grid of cell objects in the form of a matrix

class CellGrid
{
protected:
	GridSize my_grid_size; // holds the details about the 
	std::vector<std::pair<int, int> > temp_adjoined_cells; // holds vector of adjoined cells for a given position
	std::vector<std::vector<char> > char_matrix; // holds matrix of the characters to represent
	int food_char_count = 0; // number of food spots on grid printed
	int doco_char_count = 0; // number of doco spots on grid printed
	int doco_count = 0;	// number of DOCOs on the grid
	int obstacle_count = 0; // number of Obstacles on the grid
public:
	std::vector<std::vector<Cell> > cell_matrix; // holds the matrix of cell objects
	CellGrid(int h, int w);	// creates the gridShape to the specified heightand width, then populates the cell_matrix with cell_objects initialized to each position.
	~CellGrid(); // de-allocates memory for CellGrid object
	
	void initCharMatrix(int world_w, int world_h); // Initialize the character matrix
	void setCharMatrix(void);  // Set the char_matrix to their appropriate characters based on the status of the cells.
	std::vector<std::pair<int, int> > findAdjoinedCells(int x, int y); // using the xand y position provided in conjunction with its data on the cell matrix, finds the cells within one space of it(N, E, S, W, NE, SE, SW, NW).
	std::vector<std::pair<int, int> > findAdjoinedOccupiedCells();  // Other doco occupied cells surrounding a doco
	std::vector<std::pair<int, int> > findAdjoinedObstacleCells();  // Obstacle Cells surounding a doco
	std::vector<std::pair<int, int> > findAdjoinedCellsFood(); // checks each of the temp_adjoining_cells and returns the matrix of cells that contain food.Using the temp variable eliminates some error checking.
	int getFoodCharCount(void); // return food_char_count
	int getDocoCharCount(void); // return doco_char_count
	int getDocoCount(void);		// return doco_count
	int getObstacleCount(void); // return obstacle_count
	std::vector<std::vector<Cell> > getMatrix(void); // returns cell_matrix
	std::vector<std::vector<char> > getCharMatrix(); // returns char_matrix
	void printCharMatrix(); // returns the character matrix in printed to the console based off of the char_matrix class property.
};

