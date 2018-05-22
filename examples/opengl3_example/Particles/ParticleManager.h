#pragma once

#include "../Timelines/Timeline.h"
#include "ParticleEffect.h"
#include "../camera.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();


	void update();
	void render(Camera *cam);

	void runEffect(Timeline *t);
	void stopEffect(Timeline *t);

	ParticleEffect* getRenderer() { return _effects[0]; }

	void printInfo();

	void deleteBlock(Block * b);

private:

	std::vector<ParticleEffect*> _effects;
};

