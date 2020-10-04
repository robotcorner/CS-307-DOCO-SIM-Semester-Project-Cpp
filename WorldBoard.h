#pragma once
#include "CellGrid.h"
#include "DataParser.h"
#include "Doco.h"
#include <vector>

// The world board is responsible for holding all the entities
// of the DOCO simulation. Creating it will create the other objects.

class WorldBoard
{
private:
	int width;
	int height;

	std::vector<std::pair<int, int> > food_positions; // will hold a matrix 
	// that will populate from the readFile() function with the positions
	// on the CellGridand amounts for some food particles. (Alternatively
	// could add them to the vector as your reading… maybe)
	std::vector<std::pair<int, int> > start_docos; // will hold a matrix that will 
	// populate from the readFile() function with the starting positions,
	// directions, etc of DOCOs. (Alternatively could add them to the vector as 
	// your reading… maybe)
	void generateFoodLocations(int x_range, int y_range, int foodCount=NULL);
	void readFile(char* inFile);

public:
	CellGrid* worldCellGrid; // will hold the CellGrid Object which contains all the Cells and GridSize
	DataParser* myParser; // the DataParser obejct for the class. 
	// DatParser = DataParser(char *filename). This filename will be DOCOData01.xml
	
	std::vector<Doco> doco_vect; // will hold a vector of all the current DOCO’s
	// on the board.These will be able to be iterated overand removed as part
	// of the vector class functionality.
	
	WorldBoard();
	WorldBoard(char* file_name);
	~WorldBoard();

	void updateCellsWithNewFood();
	void setCellWithNewFood(int x, int y);
	int  setCellWithNoFood(int x, int y);  // return the number of foods eaten, set new food to zero
	
	void updateDocos();
	int updateCellWithADoco(int x, int y);		// helper function to set cell status for cells with DOCOs, return food amount
	void updateAllDocoSurroundings();			// helper function of updateDocos()

	// TODO:: DECIDE IF I NEED THEESE!
	// function overloading because unkown if direction is provided.
	/*
    void spawnOneDocoAtPos(int x, int y);
	void spawnOneDocoAtPos(int x, int y, std::string direction);
	void spawnOneDocoAtPos(std::pair<int, int>);
	void spawnOneDocoAtPos(std::pair<int, int>, std::string direction);

	void spawnOneFoodAtPos(int x, int y);
	void spawnOneFoodAtPos(std::pair<int, int>);
	*/
	void updateWorldState(); // x and y range to update.
	void printWorld();
};
