#include "Emissions.h"
#include "ParticleEffect.h"
#include "misc/RandFunction.h"
#include "glm/geometric.hpp"

Emission::Emission(ParticleEffect* effect, Timeline *emitter)
	: _emitter(emitter), _particleInfo(), _data(), _effect(effect)
{
}


Emission::~Emission()
{
}

void Emission::stepParticle(unsigned int index, float timeStep)
{
	_data[index]._position += timeStep * _particleInfo[index]._velocity;
}

void Emission::updateParticle(float emitterTime, unsigned int index)
{
	Timeline *ref = _emitter->_particleLink;
	if (_effect->elapsedSince(_particleInfo[index]._spawnTime) >= (ref ? ref->duration() : 5.f))
	{
		//Destroy particle
		incrementCycleBegin();
		return;
	}


	// Fetch relevant blocks and apply
	BlockList active = ref ?
		ref->fetchBlocks(_effect->elapsedSince(_particleInfo[index]._spawnTime)) :
		BlockList();
	
	// Reset data that is applied relative to initial data
	_data[index]._color = glm::vec4(1.f);
	_data[index]._size = _particleInfo[index]._initSize;

	for (unsigned int i = 0; i < active._size; i++)
		active._blocks[i]->applyParticle(emitterTime, _particleInfo[index], _data[index]);

	stepParticle(index, EMIT_STEP);
	// Do some more calcs (e.g. texture assignments)..
}

void Emission::updateParticles(float emitterTime)
{
	if (_cycleEnd < _cycleBegin)
	{
		for (unsigned int i = _cycleBegin; i < _particleInfo.size(); i++)
			updateParticle(emitterTime, i);
	}
}
void Emission::spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime)
{
	float duration = _emitter->_particleLink->duration();
	// Emitt n particles (average n/time in the linear curve)
	float n = glm::mix(spawner->_params._initAmount, spawner->_params._endAmount, (blockTime + EMIT_STEP*0.5) / duration);
	float dTime = 0.016f / (n + 1.f);
	// Lazy solution, emitted particles is floored.
	// Remainder needs to be stored for next update so the number of particles emitted is correct...
	for (float i = 0; i < n; i++) 
	{
		InitialEmissionParams &param = spawner->_params;
		Particle p;
		p._spawnTime = _effect->_time + dTime * i;
		p._initSize = glm::mix(param._minSize, param._maxSize, randomFloat());
		p._initDir = glm::vec3(0, 0, 1);

		GPUParticle gpuP;
		gpuP._rotation = glm::mix(param._minRotation, param._maxRotation, randomFloat());
		gpuP._position = glm::vec3(0.f);

		// Apply emitter blocks
		for (unsigned int ii = 0; ii < active._size; ii++)
			active._blocks[ii]->applyEmitter(p, gpuP);

		// Perform post calculations
		p._velocity = glm::mix(param._minForce, param._maxForce, randomFloat()) * p._initDir;

		// Add new particle
		_particleInfo[_cycleEnd] = p;
		_data[_cycleEnd] = gpuP;
		incrementCycleEnd();
	}
}
void Emission::spawnParticles(float emitterTime)
{
	BlockList list = _emitter->fetchBlocks(emitterTime);
	BlockList spawners;

	for (unsigned int i = 0; i < list._size; i++)
	{
		SpawnBlock *b = dynamic_cast<SpawnBlock*> (list._blocks[i]);
		if (b != NULL)
		{
			spawners.push(b);
			list.remove(i--);
		}
	}
	for (unsigned int i = 0; i < spawners._size; i++)
		spawnParticle((SpawnBlock*)spawners._blocks[i], list, emitterTime - spawners._blocks[i]->_startTime);
}
