// --- FINISHED

#pragma once
#include "DocoFactory.h"
#include "DocoMoveStrategy.h"
#include "DocoMovePatternHorizontal.h"
#include "DocoMovePatternDiagonal.h"
#include "DocoMovePatternVertical.h"
#include "DocoMovePatternDefault.h"
#include "DocoMovePatternPerp.h"

// --- Private class constructor
DocoFactory::DocoFactory() {

}

// --- Public class destructor
DocoFactory::~DocoFactory() {

}

int DocoFactory::getInstanceNumber() {
	return this->instanceNumber;
}

// Static function which returns a pointer to the singleton instance of this class.
// Static variables are not destroyed when a function exits.

DocoFactory* DocoFactory::getInstance() {
	static DocoFactory* theInstance = nullptr;
	static int counter = 1;
	if (theInstance == nullptr) {
		theInstance = new DocoFactory();
		theInstance->instanceNumber = counter;
		counter++;	// If another instance is created ever, the counter will show it.
	}
	return theInstance;
}

Doco DocoFactory::createDocoDefault(int x_pos, int y_pos, std::string direction)
{
	// return a doco of random movement type
	DocoMovePatternDefault* strategy = new DocoMovePatternDefault;
	return Doco(x_pos, y_pos, direction, std::string("Random"), strategy);

}

Doco DocoFactory::createDocoDiagonal(int x_pos, int y_pos, std::string direction)
{
	// return a doco of diagonal movement type
	DocoMovePatternDiagonal* strategy = new DocoMovePatternDiagonal;
	return Doco(x_pos, y_pos, direction, std::string("Diagonal"), strategy);
}

Doco DocoFactory::createDocoHorizontal(int x_pos, int y_pos, std::string direction)
{
	// return a doco of horizontal movement type
	DocoMovePatternHorizontal* strategy = new DocoMovePatternHorizontal;
	return Doco(x_pos, y_pos, direction, std::string("Horizontal"), strategy);
}

Doco DocoFactory::createDocoVertical(int x_pos, int y_pos, std::string direction)
{
	// TODO: return a doco of vertical movement type
	DocoMovePatternVertical* strategy = new DocoMovePatternVertical;
	return Doco(x_pos, y_pos, direction, std::string("Vertical"), strategy);
}

Doco DocoFactory::createDocoPerp(int x_pos, int y_pos, std::string direction)
{
	// TODO: return a doco of perpendicular movement type
	DocoMovePatternPerp* strategy = new DocoMovePatternPerp;
	return Doco(x_pos, y_pos, direction, std::string("Perp"), strategy);
}
