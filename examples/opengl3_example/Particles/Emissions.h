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
	
	void spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime, float deltaT);
	void spawnParticles(float emitterTime, float deltaT);

	void updateParticle(unsigned int index);
	void updateParticles();

	/* Draw effect. */
	void render();
	void bindTextures();

	/*Get number of active particles */
	size_t numActive();
	/* If effect is wrapped around the circular buffer. */
	bool isLooped();
	
	Timeline* getEmitter();
	GPUParticle& operator[](unsigned int index);
	/* Get the index of the last particle. */
	unsigned int last();
	/* Check if the particle at the index is alive. */
	bool active(unsigned int index);

private:
	ParticleEffect *_effect;

	/* Timeline containing emitter blocks */
	Timeline *_emitter;
	ParticleShader *_shader;

	std::vector<Particle> _particleInfo;
	std::vector<GPUParticle> _data;

	size_t _cycleBegin, _cycleEnd;

	/* Store how many (more) particles the */
	float _remainder;

	unsigned int _bufCycle;
	ParticleBuffer _shadeBuffers[2];

	GLuint _texSlots[4];
	bool _texActive[4];

	/* Check if particle with elapsed time is dead.	*/
	bool alive(float elapsedTime);

	void incrementCycleEnd();
	void incrementCycleBegin();


	void stepParticle(unsigned int index, float timeStep);
};

