#pragma once
// Responsible for maintaining the changing game state and status.
class Simulator
{
private:
	long int turn_num = 0;
	int update_interval = 1;
	int display_interval = 1;
	bool paused_state = false;

public:
	Simulator();	// creates simulator object with default settings
	Simulator(int updateInterval, int displayInterval);	// creates the simulator with specific intervals for game updates and display updates.
	~Simulator();	// de-allocates space for the simulator object 
	void pause();	// set paused to True
	void run();		// set paused to False
	void setUpdateInterval(int);	// change the rate at which the World is updating. Adjust update_interval to the value provided.
	void setDisplayInterval(int);	// change the rate at which the World is updating on the screen. Adjust display_interval to the value provided.
	void turnInc();	// increment turn by 1;
	long int getTurnNum();	// return turn_num
	int getUpdateInterval(); // return update_interval
	int getDisplayInterval(); // return display_update_interval
	bool getPausedState(); // return paused
	void delay(int seconds_delay); // delay in seconds
};

