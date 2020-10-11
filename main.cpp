#include <iostream>
#include "Viewer.h"
#include "WorldBoard.h"
#include "Simulator.h"
#define DEBUG_1

int main() {

	int update_rate = 1;
	int display_rate = 1;
	Simulator* mySim = new Simulator(update_rate, display_rate); // containers the DocoSim Object to adjust the sim.
	long int max_updates = 10000;
	char inFile[] = "DOCOData01.xml";
	Viewer* view = new Viewer();
	WorldBoard* myDocoWorld = new WorldBoard(inFile);	
	while (!mySim->getPausedState()) // while not false
	{
		mySim->delay(3);
		system("cls");
		std::cout << view->getHeaderMessage() << "\n";
		std::cout << view->getNewSeparatorLine() << "\n";
		myDocoWorld->updateWorldState();
		myDocoWorld->printWorld();
		std::cout << view->getNewSeparatorLine() << "\n";
		std::cout << view->getFooterMessage() << "\n";
		mySim->turnInc();
		if (mySim->getTurnNum() == max_updates) mySim->pause();	
	}
	return 0;
}