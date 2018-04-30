#pragma once

#include "../Timelines/Timeline.h"
#include "ParticleEffect.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();


	void update();

	void runEffect(Timeline *t);
	void stopEffect(Timeline *t);

private:

	std::vector<ParticleEffect*> _effects;
};

