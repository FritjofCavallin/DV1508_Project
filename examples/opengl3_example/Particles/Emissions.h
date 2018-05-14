#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleShader.h"
#include "../Timelines/Timeline.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "../Timelines/EmittBlocks/SpawnBlock.h"

class ParticleEffect;

class Emission
{
public:
	Emission(ParticleEffect* effect, Timeline *emitter, ParticleShader *shader);
	~Emission();

	/* Timeline containing emitter blocks */
	Timeline *_emitter;
	ParticleShader *_shader;

	std::vector<Particle> _particleInfo;
	std::vector<GPUParticle> _data;

	void spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime, float deltaT);
	void spawnParticles(float emitterTime, float deltaT);

	void updateParticle(unsigned int index);
	void updateParticles();


	void render();

	/*Get number of active particles */
	size_t numActive();
	bool isLooped() {	return _cycleEnd < _cycleBegin; }

private:
	ParticleEffect *_effect;
	size_t _cycleBegin, _cycleEnd;

	/* Store how many (more) particles the */
	float _remainder;

	unsigned int _bufCycle;
	ParticleBuffer _shadeBuffers[2];

	void incrementCycleEnd() { _cycleEnd++; if (_cycleEnd == _particleInfo.size()) _cycleEnd = 0; }
	void incrementCycleBegin() { _cycleBegin++; if (_cycleBegin == _particleInfo.size()) _cycleBegin = 0; }



	void stepParticle(unsigned int index, float timeStep);
};

