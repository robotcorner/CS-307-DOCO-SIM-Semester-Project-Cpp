#pragma once
#include "DocoFactory.h"
#include "DocoMoveStrategy.h"
#include "DocoMovePatternHorizontal.h"
#include "DocoMovePatternDiagonal.h"
#include "DocoMovePatternVertical.h"
#include "DocoMovePatternDefault.h"
#include "DocoMovePatternPerp.h"

// --- Private class constructor
DocoFactory::DocoFactory() : AbstractSimpleDocoFactory() {

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

Doco* DocoFactory::createDocoDefault(int x_pos, int y_pos, std::string dir)
{
	// --- Return a doco of random movement type
	DocoMovePatternDefault* strategy = new DocoMovePatternDefault();
	std::string patternName = std::string("Random");
	Doco* newDoco = new Doco(x_pos, y_pos, dir, patternName);
	newDoco->setPtrMoveStrategy(strategy);
	return newDoco;
}

Doco* DocoFactory::createDocoDiagonal(int x_pos, int y_pos, std::string dir)
{
	// --- Return a doco of diagonal movement type
	DocoMovePatternDiagonal* strategy = new DocoMovePatternDiagonal();
	std::string patternName = std::string("Diagonal");
	Doco* newDoco = new Doco(x_pos, y_pos, dir, patternName);
	newDoco->setPtrMoveStrategy(strategy);
	return newDoco;
}
Doco* DocoFactory::createDocoHorizontal(int x_pos, int y_pos, std::string dir)
{
	// --- Return a doco of horizontal movement type
	DocoMovePatternHorizontal* strategy = new DocoMovePatternHorizontal();
	std::string patternName = std::string("Horizontal");
	Doco* newDoco = new Doco(x_pos, y_pos, dir, patternName);
	newDoco->setPtrMoveStrategy(strategy);
	return newDoco;
}

Doco* DocoFactory::createDocoVertical(int x_pos, int y_pos, std::string dir)
{
	// --- Return a doco of vertical movement type
	DocoMovePatternVertical* strategy = new DocoMovePatternVertical();
	std::string patternName = std::string("Vertical");
	Doco* newDoco = new Doco(x_pos, y_pos, dir, patternName);
	newDoco->setPtrMoveStrategy(strategy);
	return newDoco;
}

Doco* DocoFactory::createDocoPerp(int x_pos, int y_pos, std::string dir)
{
	// --- Return a doco of perpendicular movement type
	DocoMovePatternPerp* strategy = new DocoMovePatternPerp();
	std::string patternName = std::string("Perp");
	Doco* newDoco = new Doco(x_pos, y_pos, dir, patternName);
	newDoco->setPtrMoveStrategy(strategy);
	return newDoco;
}
