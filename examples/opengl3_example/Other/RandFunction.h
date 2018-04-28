#pragma once

#include<random>


/*	Seed the rand() function from the random_device
*/
void seedRand();

/* Generate a random initializer list with random numbers generated trough the random_device.
*/
std::vector<std::random_device::result_type> generateSeedSeq(unsigned int seedCount);

/*
Use rand() to generate a random float between [0-1]
*/
float randomFloat();
/*
Use rand() to generate a random float between [0-max]
*/
float randomFloat(float max);
/*
Use rand() to generate a random float between [min-max]
*/
float randomFloat(float min, float max);
/*
Use rand() to generate a random int between [0-max]
*/
int randomInt(int max);
/*
Use rand() a random int between [min-max]
*/
int randomInt(int min, int max);
/*
Use rand() to generate a random boolean value
*/
bool randomBool();

#pragma once
