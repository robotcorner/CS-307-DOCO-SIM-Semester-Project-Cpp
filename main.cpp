#include <iostream>
#include "Viewer.h"
#include "WorldBoard.h"
#include "Simulator.h"
#define DEBUG_1

int main() {
	int update_rate = 1;
	int display_rate = 1;
	Simulator* mySim = new Simulator(update_rate, display_rate); // containers the DocoSim Object to adjust the sim.
	long int max_updates = 100;
	
	char inFile[] = "DOCOData01.xml";
	WorldBoard* myDocoWorld = new WorldBoard(inFile);
	Viewer view = Viewer();

	// Initialize World.
	while (mySim->getPausedState())
		std::cout << view.getHeaderMessage() << endl;
		std::cout << view.getNewSeparatorLine() << endl;
		mySim->delay(1);
		myDocoWorld->updateWorldState();
		myDocoWorld->printWorld();
		myDocoWorld->printWorld();
		mySim->turnInc();
		if (mySim->getTurnNum() == max_updates) mySim->pause();
		std::cout << view.getNewSeparatorLine() << endl;
		std::cout << view.getLineCountWorld() << endl;
		std::cout << view.getFooterMessage() << endl;
	return 0;
}