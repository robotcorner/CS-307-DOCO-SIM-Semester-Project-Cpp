#pragma once
#include <random>
#include "UniformRandom.h"

// TODO: Declare as a singleton?

std::random_device seed; // initialize seed engine
std::mt19937 rng(seed()); // generate random num with Merseene_Twister engine

UniformRandom::UniformRandom() 
{
	this->active = true;
}

UniformRandom* UniformRandom::getInstance() 
{
	static UniformRandom* theInstance = nullptr;
	static int counter = 1;
	if (theInstance == nullptr) {
		theInstance = new UniformRandom();
		theInstance->instanceNumber = counter;
		counter++;	// If another instance is created ever, the counter will show it.
	}
	return theInstance;
}

int UniformRandom::generateRandomNum(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max);
	auto rand_int = uni(rng);
	return rand_int;
}

int UniformRandom::getInstanceNumber() 
{
	return this->instanceNumber;
}

