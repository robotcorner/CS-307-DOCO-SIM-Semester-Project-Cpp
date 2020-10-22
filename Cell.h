#pragma once
#include <string>
class Cell
{
	// Cells are rigid objects on the board, they don’t move or change positions.
	// There will be many of these mapped onto a Cell Grid.
private:
	int x_pos;					// x position of a cell
	int y_pos;					// y position of a cell
	bool obstacle = false;		// whether the cell is an obstacle
	bool occupied = false;		// whether a cell is currently occupied by a DOCO or other organism.
	std::string strategy = "horizontal";		// indicates the strategy of the Doco on the cell
	bool food_present = false;	// whether there is food present in a cell so that the DOCO can smell it and go to it when nearby
	int food_count = 0;			// food count in the cell
	char symbol = '-';			// symbol to print to the board for the location empty cell

public:
	Cell(int x, int y); // create the cell object, it can not be created without a position on the board.
	~Cell();

	int getXPos(void);			// return the x_pos of the Cell
	int getYPos(void);			// returns the y_pos of the Cell
	bool getOccupied(void);		// returns whether or not the cell is occupied by a DOCO
	bool getObstacle(void);		// returns whether or not the cell is an obstable
	bool getFoodPresent(void);	// returns whether food is present or not in the cell
	int getFoodCount(void);		// returns the number of food pellets in the cell
	char getSymbol(void);		// gets the character symbol for this cell
	void setOccupied(bool);		// set whether the cell is occupied or not by a DOCO
	void setStrategy(std::string); // set strategy for the cell
	void setSymbol();			// set the symbol for the grid based off whether it’s occupied or not, or food is present. 
	void setCustomSymbol(char);	// set character symbol for the cell to the char provided.
	void setFoodPresent();		// set whether there is any food in the cell based on food _count
	void addFood(int);			// add food to the Cell with the amount specified
	void removeFood(int);		// remove food pellets from cell with amount specified
	void removeAllFood(void);	// set the food count to zero
};
