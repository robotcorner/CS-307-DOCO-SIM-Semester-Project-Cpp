#pragma once
class UniformRandom
{
private:
	int instanceNumber = 0;			// counter to show 1 instance only
	bool active = false;
public:
	UniformRandom();	// private constructor
	~UniformRandom();	// public destructor
	int getInstanceNumber();		// return the number of this instance

	// The following function is declared as a static member.  This means
	// that it can be called using the syntax AbstractSimpleDocoFactory::getInstance()
	// without having to have an instance of the class already created.
	// It holds a single static pointer to a AbstractSimpleDocoFactory object
	static UniformRandom* getInstance();
	int generateRandomNum(int min, int max);
};
