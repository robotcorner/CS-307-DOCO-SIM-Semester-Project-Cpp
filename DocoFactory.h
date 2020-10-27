#pragma once
#include "AbstractSimpleDocoFactory.h"
#include "Doco.h"
#include <string>

// Factory to Produce Docos
// Implemented as a Singleton

// HOW TO USE:
// DocoFactory* SimpDocoFactory = DocoFactory::getInstance();

class DocoFactory : public AbstractSimpleDocoFactory
{
	private:
		int instanceNumber = 0;			// counter to show 1 instance only
		DocoFactory();	// private constructor
	public:
		~DocoFactory();	// public destructor
		int getInstanceNumber();		// return the number of this instance

		// The following function is declared as a static member.  This means
		// that it can be called using the syntax AbstractSimpleDocoFactory::getInstance()
		// without having to have an instance of the class already created.
		// It holds a single static pointer to a AbstractSimpleDocoFactory object
		static DocoFactory* getInstance();

		Doco* createDocoDefault(int x_pos, int y_pos, std::string dir);
		Doco* createDocoDiagonal(int x_pos, int y_pos, std::string dir);
		Doco* createDocoHorizontal(int x_pos, int y_pos, std::string dir);
		Doco* createDocoVertical(int x_pos, int y_pos, std::string dir);
		Doco* createDocoPerp(int x_pos, int y_pos, std::string dir);

};

