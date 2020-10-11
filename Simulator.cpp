#include "Simulator.h"
#include <chrono>
#include <thread>

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
	this->paused_state = true;
}

void Simulator::run()
{
	this->paused_state = false;
}

void Simulator::setUpdateInterval(int newInterval)
{
	// Based off how time is implemented, limit the max 
	// and lowest values. Set to max or lowest if it 
	// exceeds or doesn't meet minimum.
	this->update_interval = newInterval;
}

void Simulator::setDisplayInterval(int newInterval)
{
	this->display_interval = newInterval; 
	// add error handling to ignore anything to fast and set to it's
	// ideal maximum
}

void Simulator::turnInc() {
	this->turn_num += 1;
}

long int Simulator::getTurnNum()
{
	return this->turn_num;
}

int Simulator::getUpdateInterval()
{
	return this->update_interval;
}

int Simulator::getDisplayInterval()
{
	return this->display_interval;
}

bool Simulator::getPausedState()
{
	return this->paused_state;
}

void Simulator::delay(int seconds_delay) {
	using namespace std::this_thread; // sleep_for, sleep_until
	using namespace std::chrono;	  // nanoseconds, system_clock, seconds
	sleep_for(nanoseconds(10));
	sleep_until(system_clock::now() + seconds(seconds_delay));
}