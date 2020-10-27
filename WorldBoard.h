#pragma once
#include "CellGrid.h"
#include "DataParser.h"
#include "AbstractDoco.h"
#include "Doco.h"
#include <vector>

// The world board is responsible for holding all the entities
// of the DOCO simulation. Creating it will create the other objects.

class WorldBoard
{
private:
	int width;
	int height;
	std::vector<std::pair<int, int> > food_positions;
	std::vector<std::pair<int, int> > obstacle_positions;
	void generateFoodLocations(int x_range, int y_range, int foodCount=NULL);
	void readFile(char* inFile);

public:
	CellGrid* worldCellGrid; // will hold the CellGrid Object which contains all the Cells and GridSize
	DataParser* myParser; // the DataParser obejct for the class. 
	std::vector<Doco> doco_vect; // will hold a vector of all the current DOCO�s on the board.
	
	WorldBoard();
	WorldBoard(char* file_name);
	~WorldBoard();

	void updateCellsWithNewFood();
	void setCellWithNewFood(int x, int y);
	int  setCellWithNoFood(int x, int y);  // return the number of foods eaten, set new food to zero
	Doco* copyDoco();
	void updateDocos();
	int updateCellWithADoco(int x, int y);		// helper function to set cell status for cells with DOCOs, return food amount
	void updateWorldState(); // x and y range to update.
	void printWorld();
};
