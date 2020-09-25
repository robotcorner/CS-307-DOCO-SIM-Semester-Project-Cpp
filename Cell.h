#pragma once
class Cell
{
private:
	int x_pos;			// x position of a cell
	int y_pos;			// y position of a cell
	bool occupied;		// whether a cell is currently occupied by a DOCO or other organism.
	bool food_present;	// whether there is food present in a cell so that the DOCO can smell it and go to it when nearby
	int food_count;		// food count in the cell
	char symbol;		// symbol to print to the board for the location

public:
	Cell(int x, int y); // create the cell object, it can not be created without a position on the board.
	~Cell();

	int getXPos(void);
	int getYPos(void);
	bool getOccupied(void);
	bool getFoodPresent(void);
	int getFoodCount(void);
	char getSymbol(void);

	void setXPos(int);			// set the x_pos of the cell
	void setYPos(int);			// set the y_pos of the cell
	void setOccupied(bool);		// set whether the cell is occupied or not by a DOCO
	void setSymbol();			//  set the symbol for the grid based off whether it’s occupied or not, or food is present. 
	void setCustomSymbol(char);	 // set character symbol for the cell to the char provided.
	void setFoodPresent(bool);
	void addFood(int);
	void removeFood(int);
	void removeAllFood(void);
};
