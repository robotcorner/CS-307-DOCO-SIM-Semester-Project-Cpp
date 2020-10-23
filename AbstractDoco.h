#pragma once
#include <string>

class AbstractDoco
{
public:
	AbstractDoco();
	~AbstractDoco();

	virtual void addEnergy();
	virtual void eat(int, std::string);
	virtual bool getAlive();
	virtual std::pair<std::string, std::pair<int, int> > getDirection(void);
	virtual std::string getDirectionString(void);
	virtual int getEnergy();
	virtual std::pair<int, int> getPosPair(void);
	virtual int getXPos(void);
	virtual int getYPos(void);
	virtual std::pair<int, int> move(int, int);
	virtual void setAlive(bool);
	virtual void setDirection(std::string);
	virtual void setEnergy(int);
	virtual void setPos(int, int);
	virtual void setPos(std::pair<int, int>);
};

