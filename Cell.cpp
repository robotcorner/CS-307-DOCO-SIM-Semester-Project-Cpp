#include "Cell.h"

Cell::Cell(int x, int y) 
{
	this->x_pos = x;
	this->y_pos = y;
}

Cell::~Cell() 
{

}

int Cell::getXPos(void)
{
	return this->x_pos;
}

int Cell::getYPos(void)
{
	return this->y_pos;
}

bool Cell::getOccupied(void)
{
	return this->occupied;
}

bool Cell::getObstacle(void)
{
	return this->obstacle;
}


bool Cell::getFoodPresent(void)
{
	return this->food_present;
}

int Cell::getFoodCount(void)
{
	return this->food_count;
}

char Cell::getSymbol(void)
{
	return this->symbol;
}

void Cell::setOccupied(bool isOccupied)
{
	this->occupied = isOccupied;
}

void Cell::setSymbol()
{
	// The symbols are as follows : '*' = location of a DOCO,
	// '.' = one or more food pellets, and '-' = an empty cell.
	// prioritizes the occupied symbol.
	if (this->occupied) {
		if (this->strategy == "horizontal") {
			this->symbol = '=';
		}
		else if (this->strategy == "vertical") {
			this->symbol = '|';
		}
		else if (this->strategy == "diagonal") {
			this->symbol = 'X';
		}
		else {	// default DOCO movement
			this->symbol = '*';
		}
	}
	else if (this->obstacle) { // TODO: fix symbol to be superscript 2 
		this->symbol = unsigned int(0xB2); // obstacle
	}
	else if (this->food_present) { // cell with one or more food
		this->symbol = '.';
	}
	else { // empty cell
		this->symbol = '-';
	}
}

void Cell::setCustomSymbol(char newSymbol)
{
	this->symbol = newSymbol;
}

void Cell::setFoodPresent()
{
	if (this->food_count == 0) {
		this->food_present = false;
	}
	else {
		this->food_present = true;
	}
}

void Cell::addFood(int foodAdded)
{
	this->food_count += foodAdded;
}

void Cell::removeFood(int foodRemoved)
{
	this->food_count -= foodRemoved;
}

void Cell::removeAllFood(void)
{
	this->food_count = 0;
}

void Cell::setStrategy(std::string newStrat) 
{
	this->strategy = newStrat;
}