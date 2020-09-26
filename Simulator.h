#pragma once
// Responsible for maintaining the changing game state and status.
class Simulator
{
private:
	long int turns_processed = 0;	
	long int turn_num = 0;
	int update_interval = 1;
	int display_interval = 1;
	bool paused = true;

public:
	Simulator();	// creates simulator object with default settings
	Simulator(int updateInterval, int displayInterval);	// creates the simulator with specific intervals for game updates and display updates.
	~Simulator();	// de-allocates space for the simulator object 
	void pause();	// set paused to True
	void run();		// set paused to False
	void setUpdateInterval(int);	// change the rate at which the World is updating. Adjust update_interval to the value provided.
	void setDisplayInterval(int);	// change the rate at which the World is updating on the screen. Adjust display_interval to the value provided.
	long int getTurnNum();	// return turn_num
	long int getTurnsProcessed(); // return turns_processed
	int getUpdateInterval(); // return update_interval
	int getDisplayInterval(); // return display_update_interval
	bool getPausedState(); // return paused
};

