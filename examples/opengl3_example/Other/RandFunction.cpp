#include"RandFunction.h"

/*	Seed the rand() function from the random_device
*/
void seedRand() {
	std::random_device rnd;
	std::srand(rnd());
}

/* Generate a random initializer list with random numbers generated trough the random_device.
*/
std::vector<std::random_device::result_type> generateSeedSeq(unsigned int seedCount) {
	std::random_device seeder;
	std::vector<std::random_device::result_type> vec(seedCount);
	//Fetch seeds.
	for (unsigned int i = 0; i < seedCount; i++)
		vec[i] = seeder();
	return vec;
}


#pragma region Simple Random Functions

float randomFloat() {
	return std::rand() / (float)RAND_MAX;
}

float randomFloat(float max) {
	return std::rand() / (float)RAND_MAX * max;
}

float randomFloat(float min, float max) {
	return min + std::rand() / (float)RAND_MAX * (max - min);
}


int randomInt(int max) {
	return std::rand() % max;
}
int randomInt(int min, int max) {
	return min + std::rand() % (max - min);
}

bool randomBool() {
	return rand() > RAND_MAX / 2;
}

#pragma endregion

