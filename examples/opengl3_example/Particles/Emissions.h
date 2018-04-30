#pragma once

#include <vector>
#include "Particle.h"
#include "../Timelines/Timeline.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "../Timelines/EmittBlocks/SpawnBlock.h"

class ParticleEffect;


class Emission
{
public:
	Emission(ParticleEffect* effect, Timeline *emitter);
	~Emission();

	/* Timeline containing emitter blocks */
	Timeline *_emitter;

	std::vector<Particle> _particleInfo;
	std::vector<GPUParticle> _data;

	void spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime);
	void spawnParticles(float emitterTime);

	void updateParticle(unsigned int index);
	void updateParticles();


	/*Get number of active particles */
	size_t numActive();

private:
	ParticleEffect *_effect;
	size_t _cycleBegin, _cycleEnd;

	void incrementCycleEnd() { _cycleEnd++; if (_cycleEnd == _particleInfo.size()) _cycleEnd = 0; }
	void incrementCycleBegin() { _cycleBegin++; if (_cycleBegin == _particleInfo.size()) _cycleBegin = 0; }



	void stepParticle(unsigned int index, float timeStep);
};

