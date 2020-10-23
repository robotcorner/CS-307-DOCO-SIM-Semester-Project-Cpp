#include "WorldBoard.h"
#include <iostream>
#include <random>
#include "Directions.h"
#include "UniformRandom.h"
#include "AbstractSimpleDocoFactory.h"
#include "AbstractDoco.h"

// --- Initialize Directions for the World
Directions dirs = Directions();

// --- Initialize Random Number Generator
UniformRandom uniRand = UniformRandom();

// ========= WORLD BOARD CONSTRUCTOR / DESTRUCTOR ==============================

WorldBoard::WorldBoard()
{
	char inFile[] = "DOCOData02.xml";
	this->readFile(inFile);
}

WorldBoard::WorldBoard(char* inFile)
{
	this->readFile(inFile);
}

WorldBoard::~WorldBoard()
{

}

// ========= FILE READ with PARSER =============================================

void WorldBoard::readFile(char* inFile)
{
	// --- Create the Parser Object
	this->myParser = new DataParser();
	this->myParser->initParser(inFile);
	this->myParser->getInstance(inFile);
	
	// --- Parse World Size
	this->width = this->myParser->getDOCOWorldWidth();
	this->height = this->myParser->getDOCOWorldHeight();
	
	// --- Create the CellGrid given World Size
	this->worldCellGrid = new CellGrid(width, height);
	
	// --- Get number of DOCOs to Spawn from Parser
	int doco_count = this->myParser->getDOCOCount();
	std::cout << "\n\nDOCO Count: " << doco_count << "\n";
	
	// --- Get Obstacle count from Parser
	int obstacle_count = this->myParser->getObstacleCount();
	std::cout << "\n\nObstacle Count: " << doco_count << "\n";

	// --- Parser Paremeters
	char* ptr_direction = new char;
	char* ptr_strategy = new char; //Doco movement strategy
	int* ptr_x_pos = new int;
	int* ptr_y_pos = new int;
	// --- Parse all DOCO information in provided file and create DOCOs from it
	// bool DataParser::getDOCOData(char *movement, int *xpos, int *ypos) 
	//NEW
	// --- Create the factory
	DocoFactory* myDocoFactory = DocoFactory::getInstance();
	
	while (this->myParser->getDOCOData(ptr_strategy, ptr_x_pos, ptr_y_pos)) //PA2 No Direction Given
	{
		std::pair<std::string, std::pair<int, int> > dir_pair;
		std::string dir;
		// --- Spawn DOCOs at provided X, Y positions with provided movement strategy and direction if avaiable, 
		// --- otherwise they are given random movement stategy and direction.
		// --- Cases for each posible movement being passed in. None of these will activate for PA-1
		switch (*ptr_strategy) {
			case 'horizontal': 
				dir_pair = dirs.getRandomHorizontalDirectionPair();
				dir = dir_pair.first;

			case 'vertical':
				dir_pair = dirs.getRandomVerticalDirectionPair();
				dir = dir_pair.first;
			case 'diagonal':
				dir_pair = dirs.getRandomDiagonalDirectionPair();
				dir = dir_pair.first;
			case 'perpendicular':
				dir_pair = dirs.getRandomPerpDirectionPair();
				dir = dir_pair.first;
			case 'random':
				dir_pair = dirs.getRandomDirectionPair();
				dir = dir_pair.first;
			default:
				//	--- Generate a random direction. Provides pair like so: ("N", (0,1))
				strcpy(ptr_strategy,'random');
				dir_pair = dirs.getRandomDirectionPair();
				dir = dir_pair.first;
			//this->doco_vect.push_back(Doco(*ptr_x_pos, *ptr_y_pos, dir)); 
			//this->doco_vect.push_back(Doco(*ptr_x_pos, *ptr_y_pos, dir, string::direction));  // TODO add movement strategy
		}

	}
	// --- Parser Memory Management
	delete ptr_direction;
	delete ptr_strategy;
	delete ptr_x_pos;
	delete ptr_y_pos;
	this->doco_vect.shrink_to_fit();
	std::cout << "\n\nDOCO's created: " << this->doco_vect.size() << "\n";
	// --- Initialize the Char Matrix 
	this->worldCellGrid->initCharMatrix(this->width, this->height);
	// --- Create the Initial Food Locations, Given starting Food_Count
	int food_count = this->myParser->getFoodCount();
	this->generateFoodLocations(this->width, this->height, food_count);
	// --- Update the choosen new food cells with the food and change symbol for that cell position.
	this->updateCellsWithNewFood();
}

// ========= FOOD SPAWNER ======================================================

void WorldBoard::generateFoodLocations(int w, int h, int foodCount)
{
	// generate spawn locations
	int x_pos = 0;
	int y_pos = 0;
	for (int i = 0; i < foodCount; ++i)
	{
		x_pos = uniRand.generateRandomNum(0, w-1);
		y_pos = uniRand.generateRandomNum(0, h-1);
		while ((this->worldCellGrid->cell_matrix[y_pos][x_pos].getFoodCount() > 3) // Food count > 3, generate new x and y position.
			|| (this->worldCellGrid->cell_matrix[y_pos][x_pos].getOccupied()) ) // Don't spawn food in occupied cells
		{
			x_pos = uniRand.generateRandomNum(0, w-1);
			y_pos = uniRand.generateRandomNum(0, h-1);
		}
		auto location = std::make_pair(x_pos, y_pos);
		this->food_positions.push_back(location);
	}
	this->food_positions.shrink_to_fit();
}

void WorldBoard::setCellWithNewFood(int x, int y)
{
	this->worldCellGrid->cell_matrix[y][x].addFood(1);
	this->worldCellGrid->cell_matrix[y][x].setFoodPresent();
	this->worldCellGrid->cell_matrix[y][x].setSymbol();
}

void WorldBoard::updateCellsWithNewFood()
{
	for (auto food : this->food_positions) {
		this->setCellWithNewFood(food.first, food.second);
	}
	food_positions.clear(); // all new food positions have been processed.
}

// ========= DOCO ACTIONs ======================================================

int WorldBoard::setCellWithNoFood(int x, int y) 
{
	int count = this->worldCellGrid->cell_matrix[y][x].getFoodCount();
	this->worldCellGrid->cell_matrix[y][x].removeAllFood();
	return count;
}

// Helper Function for updateDocos - Makes a Cell on the grid have a DOCO Present
int WorldBoard::updateCellWithADoco(int x, int y)
{
	this->worldCellGrid->cell_matrix[y][x].setOccupied(true);
	int food_count = this->setCellWithNoFood(x, y);
	this->worldCellGrid->cell_matrix[y][x].setFoodPresent();
	this->worldCellGrid->cell_matrix[y][x].setSymbol();
	return food_count;
}

void WorldBoard::updateDocos(void)
{
	// --- Remove dead DOCOs from the list
	int size = this->doco_vect.size();
	while (size > 0)  // Go through doco_vect, delete item if it's dead
	{
		if (!this->doco_vect[size-1].getAlive()) {
			this->worldCellGrid->cell_matrix[this->doco_vect[size-1].getYPos()][this->doco_vect[size-1].getXPos()].setOccupied(false);
			this->worldCellGrid->cell_matrix[this->doco_vect[size-1].getYPos()][this->doco_vect[size-1].getXPos()].setSymbol();
			auto pos = this->doco_vect.begin() + size - 1;
			this->doco_vect.erase(pos);
			size -= 1; // remove an extra item as the doco has been erased.
		}
		size -= 1;
	}

	// --- Vars for the upcoming DOCO update loop
	int food_eaten;
	int x = 0;
	int y = 0;
	int i = 0;

	// --- Update the current cells with DOCO actions that were decided the previous turn / round.
	for (i = 0; i < this->doco_vect.size(); i++) 
	{
		// --- Current X any Y Pos
		x = this->doco_vect[i].getXPos();
		y = this->doco_vect[i].getYPos();

		// ------------------
		// --- Tell the DOCO what it's surrounding are, so it knows its options.
		this->doco_vect[i].adjoined_cells = this->worldCellGrid->findAdjoinedCells(x, y);  //Non Border Cells
		this->doco_vect[i].adjoined_occupied_cells = this->worldCellGrid->findAdjoinedOccupiedCells();  
		this->doco_vect[i].adjoined_obstacle_cells = this->worldCellGrid->findAdjoinedObstacleCells();
		this->doco_vect[i].adjoined_food_cells = this->worldCellGrid->findAdjoinedCellsFood();

		// --- Find NEW Cell to move to from available options. Chooses desirable X_Y position and assingns the DOCO with that new X_Y position
		auto moved_to = this->doco_vect[i].move(this->width, this->height);	// all doco's in list make new move decision one at a time
		// ------------------

		// --- Update it's previous cell with data on being non-occupied now.			
		this->worldCellGrid->cell_matrix[y][x].setOccupied(false);
		this->worldCellGrid->cell_matrix[y][x].setFoodPresent();
		this->worldCellGrid->cell_matrix[y][x].setSymbol();

		// --- Update cell properties of new cell DOCO is at
		// --- Eat Food for Current Cell. Gain Energy.
		food_eaten = this->updateCellWithADoco(this->doco_vect[i].getXPos(), this->doco_vect[i].getYPos());
		this->doco_vect[i].eat(food_eaten, "default");
			// TODO --- Split High Energy DOCOs if energy over 750
			// if this->doco_vect[i].getenergy() > 750 then SPLIT
			//    this->doco_vect[i].setenergy(this->doco_vect[i].getenergy()/2)
			//    CREATE NEW DOCO(REVERSE DIRECTION, other half of energy)
	
	
		
		this->worldCellGrid->cell_matrix[this->doco_vect[i].getYPos()][this->doco_vect[i].getXPos()].setOccupied(true); // set the cell as populated
		this->worldCellGrid->cell_matrix[this->doco_vect[i].getYPos()][this->doco_vect[i].getXPos()].setFoodPresent();
		this->worldCellGrid->cell_matrix[this->doco_vect[i].getYPos()][this->doco_vect[i].getXPos()].setSymbol();
	}
}

// --- Perform a SINGLE update of the WorldBoard
void WorldBoard::updateWorldState()
{
	// --- Reinitialize the Char Matrix each turn.
	this->worldCellGrid->initCharMatrix(this->width, this->height);
	// --- Find new positions to place food on the board that are not already at max capacity
	this->generateFoodLocations(this->width, this->height, uniRand.generateRandomNum(1, 10));
	// --- Update the choosen new food cells with the food and change symbol for that cell position.
	this->updateCellsWithNewFood();
	// --- Update every DOCO on the board. 
	this->updateDocos();
	// --- Run through the character status of each cell and set the matrix for it.
	this->worldCellGrid->setCharMatrix();
}

void WorldBoard::printWorld()
{
	this->worldCellGrid->printCharMatrix();
	std::cout << "DOCOs on Board:          " << this->worldCellGrid->getDocoCharCount() << "\n";
	std::cout << "DOCOs Actually Present:  " << this->doco_vect.size() << "\n";
	std::cout << "Unique Food Spots:       " << this->worldCellGrid->getFoodCharCount() << "\n";
}