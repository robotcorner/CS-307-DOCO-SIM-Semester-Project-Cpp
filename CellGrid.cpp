#include "CellGrid.h"
#include "Cell.h"
#include "GridSize.h"
#include <iostream>

// creates the gridShape to the specified heightand width, then 
// populates the cell_matrix with cell_objects initialized to each position.

CellGrid::CellGrid(int h, int w)
{
	this->my_grid_size.setHeight(h);
	this->my_grid_size.setWidth(w);
	int height = my_grid_size.getHeight();
	int width = my_grid_size.getWidth();
	this->cell_matrix = std::vector<std::vector<Cell> > (height);
	// build cell matrix
	for (auto y = 0; y < height; y++)
	{
		for (auto x = 0; x < width; x++)
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

void CellGrid::initCharMatrix(int world_w, int world_h) {
	// Set the char_matrix to their appropriate characters 
	// based on the status of the cells.
	int x = 0;
	int y = 0;
	this->char_matrix = std::vector<std::vector<char> >(world_h);
	for (y = 0; y < world_h; y++)
	{
		for (x = 0; x < world_w; x++)
		{
			this->char_matrix[y].push_back(' ');
		}
	}
}


void CellGrid::setCharMatrix(void)
{
	// Set the char_matrix to their appropriate characters 
	// based on the status of the cells.
	int x = 0;
	int y = 0;
	this->food_char_count = 0;
	this->doco_char_count = 0;
	for (y = 0; y < my_grid_size.getHeight(); y++)
	{
		for (x = 0; x < my_grid_size.getWidth(); x++)
		{
			this->char_matrix[y][x] = this->cell_matrix[y][x].getSymbol();
			if (this->cell_matrix[y][x].getFoodPresent()) this->food_char_count += 1;
			if (this->cell_matrix[y][x].getOccupied()) this->doco_char_count += 1;
			if (this->cell_matrix[y][x].getObstacle()) this->doco_char_count += 1;
		}
	}
}

// Goal: tell a DOCO what it's adjoined occupied cells are. Update the DOCOs private adjoined_food_cells matrix with this information
std::vector<std::pair<int, int> > CellGrid::findAdjoinedCells(int x, int y)
{
	// using the xand y position provided in conjunction with its data 
	// on the cell matrix, finds the cells within one space of it
	// (N, E, S, W, NE, SE, SW, NW)
	// DO logic off of borders
	this->temp_adjoined_cells.clear();
	int x_start = 0;
	int y_start = 0;
	int x_border = my_grid_size.getWidth();
	int y_border = my_grid_size.getHeight();
	std::pair<int, int> viable_pair;
	int i = 0;
	int j = 0;
	for (i = -1; i <= 1; i++) {
		for (j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			if ( ((x + i) < x_border) && ((x + i) >= x_start) && ((y + j) < y_border) && ((y + j) >= y_start))
			{
				viable_pair = std::make_pair(x + i, y + j);
				this->temp_adjoined_cells.push_back(viable_pair);
			}
		}
	}
	this->temp_adjoined_cells.shrink_to_fit();
	return this->temp_adjoined_cells;
}

// tell a DOCO what it�s adjoined occupied cells are.Update the DOCO�s
// private adjoined_occupied_cells matrix with this informatio
std::vector<std::pair<int, int> > CellGrid::findAdjoinedOccupiedCells()
{
	std::vector<std::pair<int, int> > tempOccupiedCells;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto pair : this->temp_adjoined_cells) {
		*x = pair.first;		// store x at allocated address
		*y = pair.second;		// store y at allocated address
		bool occupied = this->cell_matrix[*y][*x].getOccupied();
		if (occupied)	// if occupied
		{
			tempOccupiedCells.push_back(std::make_pair(*x, *y));
		}
	}
	delete x;
	delete y;
	return tempOccupiedCells;
}

// tell a DOCO what it�s adjoined occupied cells are.Update the DOCO�s
// private adjoined_obstacle_cells matrix with this informatio
std::vector<std::pair<int, int> > CellGrid::findAdjoinedObstacleCells()
{
	std::vector<std::pair<int, int> > tempObstacleCells;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto pair : this->temp_adjoined_cells) {
		*x = pair.first;		// store x at allocated address
		*y = pair.second;		// store y at allocated address
		bool obstacle = this->cell_matrix[*y][*x].getObstacle();
		if (obstacle)	// if occupied
		{
			tempObstacleCells.push_back(std::make_pair(*x, *y));
		}
	}
	delete x;
	delete y;
	return tempObstacleCells;
}

// tell a DOCO what it�s adjoined occupied cells are.Update the DOCO�s
// private adjoined_obstacle_cells matrix with this informatio
std::vector<std::pair<int, int> > CellGrid::findAdjoinedOpenCells()
{
	std::vector<std::pair<int, int> > tempOpenCells;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto pair : this->temp_adjoined_cells) {
		*x = pair.first;		// store x at allocated address
		*y = pair.second;		// store y at allocated address
		bool obstacle = this->cell_matrix[*y][*x].getObstacle();
		bool occupied = this->cell_matrix[*y][*x].getOccupied();
		if (!obstacle && !occupied)	// if occupied or obstacle
		{
			tempOpenCells.push_back(std::make_pair(*x, *y));
		}
	}
	delete x;
	delete y;
	return tempOpenCells;
}


// tell a DOCO what it�s adjoined cells are. Update the DOCO�s
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
	for (auto pair : this->temp_adjoined_cells) {
		*x = pair.first;		// store x at allocated address
		*y = pair.second;		// store y at allocated address
		if (this->cell_matrix[*y][*x].getFoodPresent()) // if food is present
		{
			tempFoodCells.push_back(std::make_pair(*x, *y));
		}
	}
	delete x;
	delete y;
	return tempFoodCells;
}

std::vector<std::pair<int, int> > CellGrid::findAdjoinedOpenCellsWithFood() {
	std::vector<std::pair<int, int> > tempOpenCellsWithFood;
	int* x = new int;
	int* y = new int;
	*x = 0;
	*y = 0;
	for (auto pair : this->temp_adjoined_cells) {
		*x = pair.first;		// store x at allocated address
		*y = pair.second;		// store y at allocated address
		bool obstacle = this->cell_matrix[*y][*x].getObstacle();
		bool occupied = this->cell_matrix[*y][*x].getOccupied();
		bool food = this->cell_matrix[*y][*x].getFoodPresent();
		if (!obstacle && !occupied && food)	// if occupied or obstacle
		{
			tempOpenCellsWithFood.push_back(std::make_pair(*x, *y));
		}
	}
	delete x;
	delete y;
	return tempOpenCellsWithFood;
}


// Goal: know how much food or DOCO's are on board
int CellGrid::getFoodCharCount(void) // find total food on board
{
	return this->food_char_count;
}
int CellGrid::getDocoCharCount(void)
{
	return this->doco_char_count;
}
int CellGrid::getDocoCount(void) // find total DOCOs on board
{
	return this->doco_count;
}
int CellGrid::getObstacleCount(void) // return obstacle_count
{
	return this->obstacle_count;
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
			std::cout << this->char_matrix[y][x] << ' ';
		}
		std::cout << "\n";
	}
}
