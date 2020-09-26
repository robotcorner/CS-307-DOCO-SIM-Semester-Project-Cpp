#include "CellGrid.h"
#include "Cell.h"
#include "GridSize.h"
#include <iostream>

/*Private Variables
	
	GridSize my_grid_size;		
	// holds the details about the CellGrid
	
	std::vector<std::vector<Cell> > cell_matrix;		
	// holds the matrix of cell objects
	
	std::vector<std::vector<char> > char_matrix;		
	// holds matrix of the characters to represent
	
	std::vector<std::pair<int, int> > temp_adjoined_cells; 
	// holds vector of adjoined cells for a given position

*/

// creates the gridShape to the specified heightand width, then 
// populates the cell_matrix with cell_objects initialized to each position.

CellGrid::CellGrid(int h, int w)
{
	this->my_grid_size.setHeight(h);
	this->my_grid_size.setWidth(w);
	
	// build cell matrix
	for (auto y = 0; y < my_grid_size.getHeight(); y++)
	{
		for (auto x = 0; x < my_grid_size.getWidth(); x++)
		{
			this->cell_matrix[y].push_back(Cell(x, y));
		}
	}
	this->cell_matrix.shrink_to_fit();		// removes excess allocations
}

CellGrid:: ~CellGrid() 
{
	// de-allocates memory for CellGrid object
}

void CellGrid::setCharMatrix(void)
{
	// Set the char_matrix to their appropriate characters 
	// based on the status of the cells.
	for (auto y = 0; y < my_grid_size.getHeight(); y++)
	{
		for (auto x = 0; x < my_grid_size.getWidth(); x++)
		{
			this->char_matrix[y][x] = this->cell_matrix[y][x].getSymbol();
		}
	}
}

// Goal: tell a DOCO what it’s adjoined occupied cells are. Update the DOCO’s private adjoined_food_cells matrix with this information
std::vector<std::pair<int, int> > CellGrid::findAdjoinedCells(int x, int y)
{
	// using the xand y position provided in conjunction with its data 
	// on the cell matrix, finds the cells within one space of it
	// (N, E, S, W, NE, SE, SW, NW)
	// DO logic off of borders
	int x_start = 0;
	int y_start = 0;
	int x_border = my_grid_size.getWidth();
	int y_border = my_grid_size.getHeight();
	std::pair<int, int> viable_pair = std::make_pair(x, y);
	int i;
	int j;
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) break;
			if (((x + i) < x_border) && ((x + i) > x_start) && ((y + j) < y_border) && ((x + j) > y_start))
			{
				viable_pair = std::make_pair(x + i, y + j);
				this->temp_adjoined_cells.push_back(viable_pair);
			}
		}
	}
	this->temp_adjoined_cells.shrink_to_fit();
	return this->temp_adjoined_cells;
}

// tell a DOCO what it’s adjoined occupied cells are.Update the DOCO’s
// private adjoined_occupied_cells matrix with this informatio
std::vector<std::pair<int, int> > CellGrid::findAdjoinedOccupiedCells()
{
	std::vector<std::pair<int, int> > tempOccupiedCells;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto i : this->temp_adjoined_cells) {
		i.first = *x;		// store x at allocated address
		i.first = *y;		// store y at allocated address
		if (this->cell_matrix[*x][*y].getOccupied())	// if occupied
		{
			tempOccupiedCells.push_back(std::make_pair(*x, *y));
		}
	}
	return tempOccupiedCells;
	delete x;
	delete y;
}

// tell a DOCO what it’s adjoined cells are. Update the DOCO’s
// private adjoined_cells matrix with this information.
std::vector<std::pair<int, int> > CellGrid::findAdjoinedCellsFood()
{
	// checks each of the temp_adjoining_cells and returns the 
	// matrix of cells that contain food.Using the temp variable
	// eliminates some error checking.
	std::vector<std::pair<int, int> > tempFoodCells;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto i : this->temp_adjoined_cells) {
		i.first = *x;		// store x at allocated address
		i.first = *y;		// store y at allocated address
		if (this->cell_matrix[*x][*y].getFoodPresent()) // if food is present
		{
			tempFoodCells.push_back(std::make_pair(*x, *y));
		}
	}
	return tempFoodCells;
	delete x;
	delete y;
}


// Goal: will set the possible move options for the DOCO based off 
// of the adjoined cell information it gathered.

std::vector<std::vector<Cell> > CellGrid::getMatrix(void)
{
	// returns the cell_matrix private variable
	return this->cell_matrix;
}

std::vector<std::vector<char> > CellGrid::getCharMatrix()
{
	// returns the char_matrix private variable
	return this->char_matrix;
}

void CellGrid::printCharMatrix(void)
{
	for (auto y = 0; y < my_grid_size.getHeight(); y++)
	{
		for (auto x = 0; x < my_grid_size.getWidth(); x++)
		{
			std::cout << this->char_matrix[y][x];
		}
	}
}





