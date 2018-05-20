#include "Particle.h"
#include "../Timelines/Timeline.h"
#include "../Timelines/EmittBlocks/SpawnBlock.h"
#include "../Other/RandFunction.h"


Particle::Particle()
	: _spawnTime(0.f), _initSize(1.f), _initDir(0, 1, 0), _velocity(0)
{}
bool Particle::dead(float particleTime, Timeline *particle)
{
	return particleTime >= (particle ? particle->_timeTotal.duration() : 5.f);
}

bool Particle::update(GPUParticle &data, float particleTime, Timeline *particle)
{
	if (dead(particleTime, particle))
		return true;
	// Fetch relevant blocks and apply
	BlockList active = particle ?
		particle->fetchBlocks(particleTime) :
		BlockList();

	// Reset data that is applied relative to initial data
	data._color = glm::vec4(1.f);
	data._size = _initSize;
	data._texBlend = glm::vec4(0.f);

	for (unsigned int i = 0; i < active._size; i++)
		active._blocks[i]->applyParticle(particleTime, *this, data);

	// Do some more calcs (e.g. texture assignments)..
	return false;
}


void Particle::init(InitialEmissionParams &param, float spawnTime)
{
	_spawnTime = spawnTime;
	_initSize = glm::mix(param._minSize, param._maxSize, randomFloat());
	_initDir = param._emitDir;
}



GPUParticle::GPUParticle()
	: _position(0.f), _color(1.f), _size(1.f), _rotation(0.f), _texBlend(0.f)
{
	_texArea[0] = 0;
	_texArea[1] = 0;
	_texArea[2] = 0;
	_texArea[3] = 0;
}


