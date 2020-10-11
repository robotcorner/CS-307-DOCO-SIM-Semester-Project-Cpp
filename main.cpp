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
		mySim->delay(5);
		system("cls");
		std::cout << view->getHeaderMessage() << endl;
		std::cout << view->getNewSeparatorLine() << endl;
		myDocoWorld->updateWorldState();
		myDocoWorld->printWorld();
		mySim->turnInc();
		std::cout << view->getNewSeparatorLine() << endl;
		std::cout << view->getLineCountWorld() << endl;
		std::cout << view->getFooterMessage() << endl;
		if (mySim->getTurnNum() == max_updates) mySim->pause();
		
	}
	return 0;
}