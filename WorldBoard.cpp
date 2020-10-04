#include "WorldBoard.h"
#include <iostream>
#include <random>

std::random_device seed; // initialize seed engine
std::mt19937 rng(seed()); // generate random num with Merseene_Twister engine
int generateRandomNum(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max);
	auto rand_int = uni(rng);
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
	char* direction = new char;
	int* x_pos = new int;
	int* y_pos = new int;
	while (this->myParser->getDOCOData(direction, x_pos, y_pos)) // parse all docos in file.
	{
		std::string docoDir = direction;
		std::cout << "Read in Direction: " << direction << "\n";
		this->doco_vect.push_back(Doco(*x_pos, *y_pos, docoDir)); // add to the doco_vect
	}
	delete direction;
	delete x_pos;
	delete y_pos;
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
		x_pos = generateRandomNum(0, w);
		y_pos = generateRandomNum(0, h);
		while (this->worldCellGrid->cell_matrix[y_pos][x_pos].getFoodCount() > 3) 
		{
			x_pos = generateRandomNum(0, w);
			y_pos = generateRandomNum(0, h);
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

// Helper Function for updateDocos
void WorldBoard::updateAllDocoSurroundings()
{
	int x;
	int y;
	for (auto doco : this->doco_vect)
	{
		x = doco.getXPos();
		y = doco.getYPos();
		doco.adjoined_cells = this->worldCellGrid->findAdjoinedCells(x, y);
		doco.adjoined_occupied_cells = this->worldCellGrid->findAdjoinedOccupiedCells();
		doco.adjoined_food_cells = this->worldCellGrid->findAdjoinedCellsFood();
	}
}


void WorldBoard::updateDocos(void)
{
	int food_eaten;
	// --- Check Doco's to kill first
	int size = this->doco_vect.size();
	while (size > 0) 
	{
		if (!this->doco_vect[size].getAlive()) {
			this->doco_vect.erase(this->doco_vect.begin()+size);
			size -= 1; // remove an extra item as the doco has been erased.
		}
		size -= 1;
	}
	// --- Update the current cells with DOCO actions that were decided the previous turn / round.
	for (auto doco : this->doco_vect)
	{
		food_eaten = this->updateCellWithADoco(doco.getXPos(), doco.getYPos());
		doco.eat(food_eaten, "default");
	}
	this->updateAllDocoSurroundings();

	// --- Set Move Positions for next round updates
	for (auto doco : this->doco_vect)
	{
		doco.move();	// all doco's in list make new move decision at same time
	}
}


// this does a **SINGLE** update of the board
void WorldBoard::updateWorldState()
{
	generateFoodLocations(this->width, this->height, generateRandomNum(1, 10));
	updateDocos();
}

void WorldBoard::printWorld()
{
	this->worldCellGrid->printCharMatrix();
}