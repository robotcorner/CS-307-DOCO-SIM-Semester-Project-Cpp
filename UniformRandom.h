#pragma once

// TODO: declare as a singleton

class UniformRandom
{
private:
	bool active = false;
public:
	UniformRandom();
	int generateRandomNum(int min, int max);
};

