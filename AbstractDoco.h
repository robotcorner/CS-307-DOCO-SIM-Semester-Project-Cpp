#pragma once
#include <string>

class AbstractDoco
{
public:
	virtual void addEnergy(int added_energy) = 0;
	virtual void eat(int, const std::string&) = 0;
	virtual bool getAlive() = 0;
	virtual std::pair<std::string, std::pair<int, int> > getDirection(void) = 0;
	virtual std::string getDirectionString(void) = 0;
	virtual int getEnergy() = 0;
	virtual std::pair<int, int> getPosPair(void) = 0;
	virtual int getXPos(void) = 0;
	virtual int getYPos(void) = 0;
	virtual std::pair<int, int> move(int, int) = 0;
	virtual void setAlive(bool) = 0;
	virtual void setDirection(std::string) = 0;
	virtual void setEnergy(int) = 0;
	virtual void setPos(int, int) = 0;
	virtual void setPos(std::pair<int, int>) = 0;
};

