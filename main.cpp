#include <iostream>
#include "Viewer.h"
#include "WorldBoard.h"
#include "Simulator.h"
#define DEBUG_1

int main() {

	#ifdef DEBUG_1
	std::cout << "Hi";
	#endif	
	// Not sure I'm using update rate or display rate right ....

	int update_rate = 1;
	int display_rate = 1;
	Simulator* mySim = new Simulator(update_rate, display_rate); // containers the DocoSim Object to adjust the sim.
	long int max_updates = 100;
	
	char inFile[] = "DOCOData01.xml";
	WorldBoard* myDocoWorld = new WorldBoard(inFile);
	while (mySim->getPausedState())
		myDocoWorld->updateWorldState();
		mySim->delay(1);
		myDocoWorld->printWorld();
		mySim->turnInc();
		if (mySim->getTurnNum() == max_updates) mySim->pause();
	return 0;
}