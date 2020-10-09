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
	this->generateFoodLocations(this->width, this->height, food_count);
	this->updateDocos();
}

// --- FOOD SPAWNER --------------------------------------

void WorldBoard::generateFoodLocations(int w, int h, int foodCount)
{
	// generate spawn locations
	int x_pos;
	int y_pos;
	for (int i = 0; i < foodCount; ++i)
	{
		x_pos = generateRandomNum2(0, w);
		y_pos = generateRandomNum2(0, h);
		while (this->worldCellGrid->cell_matrix[y_pos][x_pos].getFoodCount() > 3) 
		{
			x_pos = generateRandomNum2(0, w);
			y_pos = generateRandomNum2(0, h);
		}
		auto location = std::make_pair(x_pos, y_pos);
		this->food_positions.push_back(location);
	}
	this->food_positions.shrink_to_fit();
}

void WorldBoard::updateCellsWithNewFood() 
{
	for (auto food : this->food_positions) {
		this->setCellWithNewFood(food.first, food.second);
	}
	food_positions.clear();
}

void WorldBoard::setCellWithNewFood(int x, int y)
{
	this->worldCellGrid->cell_matrix[y][x].addFood(1);
}


// --- DOCO ACTIONs ------------------------------------------

int WorldBoard::setCellWithNoFood(int x, int y) 
{
	int count = this->worldCellGrid->cell_matrix[y][x].getFoodCount();
	this->worldCellGrid->cell_matrix[y][x].removeAllFood();
	return count;
}

// Helper Function for updateDocos
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
	while (size > 0) 
	{
		if (!this->doco_vect[size-1].getAlive()) {
			this->doco_vect.erase(this->doco_vect.begin()+size-1);
			size -= 1; // remove an extra item as the doco has been erased.
		}
		size -= 1;
	}
	// --- Update the current cells with DOCO actions that were decided the previous turn / round.
	int x;
	int y;
	for (auto doco : this->doco_vect)
	{
		x = doco.getXPos();
		y = doco.getYPos();
		doco.adjoined_cells = this->worldCellGrid->findAdjoinedCells(x, y); // TODO: fix, returns single cell
		doco.adjoined_occupied_cells = this->worldCellGrid->findAdjoinedOccupiedCells();
		food_eaten = this->updateCellWithADoco(x, y);
		doco.eat(food_eaten, "default");
		doco.adjoined_food_cells = this->worldCellGrid->findAdjoinedCellsFood();

	}
	// --- Set Move Positions for next round updates
	for (auto doco : this->doco_vect)
	{
		doco.move();	// all doco's in list make new move decision one at a time
	}
}


// this does a **SINGLE** update of the board
void WorldBoard::updateWorldState()
{
	generateFoodLocations(this->width, this->height, generateRandomNum2(1, 10));
	updateDocos();
}

void WorldBoard::printWorld()
{
	this->worldCellGrid->printCharMatrix();
}