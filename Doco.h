#pragma once
#include <string>
#include <vector>

//DOCO

class Doco
{
private:
	bool alive;	// whether or not the DOCO is alive or dead, if it�s dead it should be removed or become invisible on the screen.
	std::pair<int, int> position; // the x position of the DOCO, the y position of the DOCO
	int energy_level; // the amount of energy the DOCO has.It will be initialized to 500 by default.
	std::string direction; // A direction that the DOCO is currently heading. It will be be one of the following strings �N�, �NE�, �E�, �SE�, �S�, �SW�, �W�, �NW�.
	std::vector<std::pair<int, int> > adjoined_cells; // this will contain the matrix of adjoining cells to a DOCO.Adjoining means only the cells are touching, diagonal included.
	std::vector<std::pair<int, int> > adjoined_occupied_cells; // this will contain the matrix of adjoining cells that are occupied.
	std::vector<std::pair<int, int> > adjoined_food_cells; // this will contain the matrix of adjoining cells that contain food. This is why the Cell object has a food_present boolean property.
	std::vector<std::pair<int, int> > move_options; // this will contain the matrix of movement options that are available to the DOCO based on it�s movement preferencesand requirements.
public:
	Doco(int, int, std::string); // starting position, x, y, direction
	// creates a DOCO object with  set positionand direction specified.These will come out of the xml file that the DataParser reads.
	~Doco();
	void setPos(int x, int y); // updates the x and y position of the DOCO.
	void setPos(std::pair<int, int>);
	void setDirection(std::string); // sets the direction of the DOCO, this will be one of the following strings �N�, �NE�, �E�, �SE�, �S�, �SW�, �W�, �NW�.Upon initialization this will be random or taken from the read in file.
	void setAlive(bool); // updates the alive status of the DOCO.
	void setEnergy(int); // set the energy_level of the DOCO to a specified amount.
	void addEnergy(int); // add the specified amount of energy to the DOCO�s energy_level
	void eat(void);	// eats the food on it's current cell
	// the DOCO regenerates 50 energy for each pellet eaten, 
	// and it eats all the pellets at this location. This call the
	// CellGrid.Matrix.SpecificCell.setFoodPresent(bool) and setSymbol(char),
	// removeAllFood() commands for the cell being eaten off of.
	void setAdjoinedCells(std::vector<std::pair<int, int> >); // tell a DOCO what it�s adjoined cells are. Update the DOCO�s private adjoined_cells matrix with this information.
	void setAdjoinedOccupiedCells(std::vector<std::pair<int, int> >); //  tell a DOCO what it�s adjoined occupied cells are.Update the DOCO�s private adjoined_occupied_cells matrix with this information.
	void setAdjoinedFoodCells(std::vector<std::pair<int, int> >); // tell a DOCO what it�s adjoined occupied cells are. Update the DOCO�s private adjoined_food_cells matrix with this information
	void setMoveOptions(void); // will set the possible move options for the DOCO based off of the adjoined cell information it gathered.
	void move(void); // using it�s private information about direction, adjoining_cells, 
	// adjoining_occupied_cells, adjoining_food_cells, return a new x and y position
	// for it to jump to from it�s available options.It will prioritize it�s current 
	// direction, but if it�s compromisedand the DOCO would run into another one or 
	// the end of the world it will pick a new random direction to move. If there are
	// no cell_options available, it will move to it�s current location for this turn.
	// Moving will also subtract 10 units of energy from the DOCO.
	void move(int, int); // choose your own move
	void move(std::vector<std::pair<int, int> >); // choose your own move
	bool getAlive(); // returns whether the DOCO is alive or dead.
	std::pair<int, int> getPosPair(void); // returns the current position of the DOCO
	int getXPos(); // returns whether the DOCO is alive or dead.
	int getYPos(); // returns the current position of the DOCO
	int getDirection(); // returns the current direction of the DOCO
	int getEnergy(); // returns the energy_level of the DOCO
	std::vector<std::pair<int, int> > getAdjoinedCells(void); // returns the object�s adjoined_cells data
	std::vector<std::pair<int, int> > getAdjoinedOccupiedCells(void); // returns the object�s adjoined_occupied_cells data
	std::vector<std::pair<int, int> > getAjoinedFoodCells(void); // returns the object�s adjoined_food_cells data
	std::vector<std::pair<int, int> > getMoveOptions(void); // returns the object�s move_options data
};
