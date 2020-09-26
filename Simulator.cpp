#include "Simulator.h"

Simulator::Simulator() {

}

Simulator::Simulator(int updateInterval, int displayInterval)
{
	this->update_interval = updateInterval;
	this->display_interval = displayInterval;
}

Simulator::~Simulator()
{

}

void Simulator::pause() 
{
	this->paused = true;
}

void Simulator::run()
{
	this->paused = false;
}

void Simulator::setUpdateInterval(int newInterval)
{
	// Based off how time is implemented, limit the max 
	// and lowest values. Set to max or lowest if it 
	// exceeds or doesn't meet minimum.
	this->update_interval = newInterval;
}

long int Simulator::getTurnNum()
{
	return this->turn_num;
}

long int Simulator::getTurnsProcessed()
{
	return this->turns_processed;
}

int Simulator::getUpdateInterval()
{
	return this->update_interval;
}

int Simulator::getPausedState()
{
	return this->paused;
}
