#pragma once

#include <vector>
#include "Particle.h"

class Emissions
{
public:
	Emissions();
	~Emissions();


	std::vector<Particle> _particleInfo;
	std::vector<GPUParticle> _data;


	void spawnParticle();
};

