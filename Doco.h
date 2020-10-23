#pragma once
#include <string>
#include <vector>
#include "AbstractDoco.h"
#include "DocoMoveStrategy.h"

class Doco : public AbstractDoco
{
private:
	DocoMoveStrategy* ptr_moveStrategy; // specifies the move strategy of the Doco
	std::string strategy;
	bool alive;	// whether or not the DOCO is alive or dead, if it’s dead it should be removed or become invisible on the screen.
	std::pair<int, int> position; // the x position of the DOCO, the y position of the DOCO
	int energy_level = 500; // the amount of energy the DOCO has.It will be initialized to 500 by default.
	std::pair<std::string, std::pair<int, int> > direction; // A direction that the DOCO is currently heading. It will be be one of the following strings “N”, “NE”, “E”, “SE”, “S”, “SW”, “W”, “NW”.
public:
	std::vector<std::pair<int, int> > adjoined_cells; // this will contain the matrix of adjoining cells to a DOCO.Adjoining means only the cells are touching, diagonal included.
	std::vector<std::pair<int, int> > adjoined_occupied_cells; // this will contain the matrix of adjoining cells that are occupied.
	std::vector<std::pair<int, int> > adjoined_obstacle_cells; // this will contain the matrix of adjoining cells that are obstacles.
	std::vector<std::pair<int, int> > adjoined_food_cells; // this will contain the matrix of adjoining cells that contain food. This is why the Cell object has a food_present boolean property.
	std::vector<std::pair<int, int> > move_options; // this will contain the matrix of movement options that are available to the DOCO based on it’s movement preferencesand requirements.
	std::vector<std::pair<int, int> > food_move_options; 

	Doco(int x, int y, std::string& start_dir, std::string& strategy, DocoMoveStrategy* strat); // starting position, x, y, direction
	// creates a DOCO object with  set positionand direction specified.These will come out of the xml file that the DataParser reads.
	~Doco();
	void setPos(int x, int y); // updates the x and y position of the DOCO.
	void setPos(std::pair<int, int>);
	void setDirection(std::string); // sets the direction of the DOCO, this will be one of the following strings “N”, “NE”, “E”, “SE”, “S”, “SW”, “W”, “NW”.Upon initialization this will be random or taken from the read in file.
	void setStrategy(std::string);
	void setPtrMoveStrategy(DocoMoveStrategy*);
	void setAlive(bool); // updates the alive status of the DOCO to passed in value.
	void setAlive(void); // updates based on energy value.
	void setEnergy(int); // set the energy_level of the DOCO to a specified amount.
	void addEnergy(int); // add the specified amount of energy to the DOCO’s energy_level
	void eat(int, const std::string&);	// eats the food on it's current cell, type is if new food types are added
	// the DOCO regenerates 50 energy for each pellet eaten, and it eats all the pellets at this location.
	std::pair<int, int> move(int, int); // using it’s private information about direction, adjoining_cells, 
	// adjoining_occupied_cells, adjoining_food_cells, return a new x and y position
	// for it to jump to from it’s available options.It will prioritize it’s current 
	// direction, but if it’s compromisedand the DOCO would run into another one or 
	// the end of the world it will pick a new random direction to move.
	// Moving will also subtract 10 units of energy from the DOCO.
	bool getAlive(); // returns whether the DOCO is alive or dead.
	std::pair<int, int> getPosPair(void); // returns the current position of the DOCO
	int getXPos(); // returns whethser the DOCO is alive or dead.
	int getYPos(); // returns the current position of the DOCO
	std::pair<std::string, std::pair<int, int> > getDirection(void); // returns the current direction of the DOCO
	std::string getDirectionString(void);
	int getEnergy(); // returns the energy_level of the DOCO
};
