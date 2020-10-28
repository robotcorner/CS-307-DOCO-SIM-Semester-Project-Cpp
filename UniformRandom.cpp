#pragma once
#include <random>
#include "UniformRandom.h"

// TODO: Declare as a singleton?

std::random_device seed; // initialize seed engine
std::mt19937 rng(seed()); // generate random num with Merseene_Twister engine

UniformRandom::UniformRandom() {
	this->active = true;
}

int UniformRandom::generateRandomNum(int min, int max) {
	std::uniform_int_distribution<int> uni(min, max);
	auto rand_int = uni(rng);
	return rand_int;
}