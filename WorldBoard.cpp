#include "WorldBoard.h"
#include <iostream>
#include <random>
#include "Directions.h"

Directions dirs = Directions();

std::random_device seed2; // initialize seed engine
std::mt19937 rng2(seed2()); // generate random num with Merseene_Twister engine
int generateRandomNum2(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max);
	auto rand_int = uni(rng2);
	return rand_int;
}

WorldBoard::WorldBoard()
{
	char inFile[] = "DOCOData01.xml";
	this->readFile(inFile);
}

WorldBoard::WorldBoard(char* inFile)
{
	this->readFile(inFile);
}

WorldBoard::~WorldBoard()
{

}

void WorldBoard::readFile(char* inFile)
{
	this->myParser = new DataParser(inFile);
	this->width = this->myParser->getDOCOWorldWidth();
	this->height = this->myParser->getDOCOWorldHeight();
	this->worldCellGrid = new CellGrid(width, height);
	int doco_count = this->myParser->getDOCOCount();
	int food_count = this->myParser->getFoodCount();
	// For initial doco spawn
	char* ptr_direction = new char;
	int* ptr_x_pos = new int;
	int* ptr_y_pos = new int;
	while (this->myParser->getDOCOData(ptr_direction, ptr_x_pos, ptr_y_pos)) // parse all docos in file.
	{
		std::pair<std::string, std::pair<int, int> > dir_pair;
		std::string dir;
		switch (*ptr_direction) {
			case 'N': 
			case 'NE':
			case 'E':
			case 'SE':
			case 'S':
			case 'SW':
			case 'W':
			case 'NW':
				dir = reinterpret_cast<char*>(*ptr_direction);
				this->doco_vect.push_back(Doco(*ptr_x_pos, *ptr_y_pos, dir)); // add to the doco_vect
			default:
				dir_pair = dirs.getRandomDirectionPair();
				dir = dir_pair.first;
				this->doco_vect.push_back(Doco(*ptr_x_pos, *ptr_y_pos, dir)); // add to the doco_vect
		}
	}
	delete ptr_direction;
	delete ptr_x_pos;
	delete ptr_y_pos;
	this->doco_vect.shrink_to_fit();
	this->worldCellGrid->initCharMatrix(this->width, this->height);
	// this->generateFoodLocations(this->width, this->height, food_count);
	// this->updateDocos();
}

// --- FOOD SPAWNER --------------------------------------

void WorldBoard::generateFoodLocations(int w, int h, int foodCount)
{
	// generate spawn locations
	int x_pos = 0;
	int y_pos = 0;
	for (int i = 0; i < foodCount; ++i)
	{
		x_pos = generateRandomNum2(0, w-1);
		y_pos = generateRandomNum2(0, h-1);
		while (this->worldCellGrid->cell_matrix[y_pos][x_pos].getFoodCount() > 3) // Food count > 3, generate new x and y position.
		{
			x_pos = generateRandomNum2(0, w-1);
			y_pos = generateRandomNum2(0, h-1);
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

// --- DOCO ACTIONs ------------------------------------------

int WorldBoard::setCellWithNoFood(int x, int y) 
{
	int count = this->worldCellGrid->cell_matrix[y][x].getFoodCount();
	this->worldCellGrid->cell_matrix[y][x].removeAllFood();
	return count;
}

// Helper Function for updateDocos  // Makes a Cell on the grid have a DOCO Present
int WorldBoard::updateCellWithADoco(int x, int y)
{
	this->worldCellGrid->cell_matrix[y][x].setXPos(x);
	this->worldCellGrid->cell_matrix[y][x].setYPos(y);
	this->worldCellGrid->cell_matrix[y][x].setOccupied(true);
	int food_count = this->setCellWithNoFood(x, y);
	this->worldCellGrid->cell_matrix[y][x].setFoodPresent();
	this->worldCellGrid->cell_matrix[y][x].setSymbol();
	return food_count;
}

void WorldBoard::updateDocos(void)
{
	int food_eaten;
	// --- Check Doco's to kill first
	int size = this->doco_vect.size();
	while (size > 0)  // Go through doco_vect, delete item if it's dead
	{
		if (!this->doco_vect[size-1].getAlive()) {
			this->doco_vect.erase(this->doco_vect.begin()+size-1);
			size -= 1; // remove an extra item as the doco has been erased.
		}
		size -= 1;
	}
	// --- Update the current cells with DOCO actions that were decided the previous turn / round.
	int x = 0;
	int y = 0;
	int i = 0;
	for (i = 0; i < this->doco_vect.size(); i++) 
	{
		x = this->doco_vect[i].getXPos();
		y = this->doco_vect[i].getYPos();
		this->doco_vect[i].adjoined_cells = this->worldCellGrid->findAdjoinedCells(x, y); // TODO: fix, returns single cell for edge cell
		this->doco_vect[i].adjoined_occupied_cells = this->worldCellGrid->findAdjoinedOccupiedCells();
		this->doco_vect[i].adjoined_food_cells = this->worldCellGrid->findAdjoinedCellsFood();
		this->doco_vect[i].move(this->width, this->height);	// all doco's in list make new move decision one at a time
		food_eaten = this->updateCellWithADoco(x, y);
		this->doco_vect[i].eat(food_eaten, "default");
		// Reset Symbols for Old Cell
		this->worldCellGrid->cell_matrix[y][x].setOccupied(false);
		this->worldCellGrid->cell_matrix[y][x].setFoodPresent();
		this->worldCellGrid->cell_matrix[y][x].setSymbol();
	}
}

// this does a **SINGLE** update of the board
void WorldBoard::updateWorldState()
{
	this->worldCellGrid->initCharMatrix(this->width, this->height);
	this->generateFoodLocations(this->width, this->height, generateRandomNum2(1, 10));
	this->updateCellsWithNewFood();
	this->updateDocos();
	this->worldCellGrid->setCharMatrix();
}

void WorldBoard::printWorld()
{
	this->worldCellGrid->printCharMatrix();
}