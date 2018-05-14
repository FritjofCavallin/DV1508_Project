#include "Emissions.h"
#include "ParticleEffect.h"
#include "../Other/RandFunction.h"
#include "glm/geometric.hpp"
#include "Constants.h"

Emission::Emission(ParticleEffect* effect, Timeline *emitter, ParticleShader *shader)
	: _emitter(emitter), _shader(shader), _particleInfo(PARTICLES_EMITTED_MAX), _data(PARTICLES_EMITTED_MAX), _effect(effect),
	_cycleBegin(0), _cycleEnd(0), _bufCycle(0)
{
	_shadeBuffers[0] = shader->genBuffer(PARTICLES_EMITTED_MAX);
	_shadeBuffers[1] = shader->genBuffer(PARTICLES_EMITTED_MAX);
}


Emission::~Emission()
{
	_shadeBuffers[0].destroy();
	_shadeBuffers[1].destroy();
}

void Emission::render()
{
	//Buffer data
	if (isLooped())
	{
		size_t N = _particleInfo.size() - _cycleBegin;
		_shadeBuffers[_bufCycle].buffer(N, _data.data() + _cycleBegin, 0);
		_shadeBuffers[_bufCycle].buffer(_cycleEnd, _data.data(), N);
	}
	else
		_shadeBuffers[_bufCycle].buffer(_cycleEnd - _cycleBegin, _data.data() + _cycleBegin, 0);
	// Swap buf and draw
	_bufCycle = !_bufCycle;
	_shadeBuffers[_bufCycle].draw();
	checkGLError();
}

void Emission::stepParticle(unsigned int index, float timeStep)
{
	_data[index]._position += timeStep * _particleInfo[index]._velocity;
}


size_t Emission::numActive()
{
	return _cycleEnd < _cycleBegin ?
		_particleInfo.size() - _cycleBegin + _cycleEnd : //Looped count
		_cycleEnd - _cycleBegin;
}

void Emission::updateParticle(unsigned int index)
{
	Timeline *ref = _emitter->_particleLink;
	float particleTime = _effect->elapsedSince(_particleInfo[index]._spawnTime);
	if (_effect->_time < _particleInfo[index]._spawnTime)
	{
		int a = 0;
	}
	if (particleTime >= (ref ? ref->_time.duration() : 5.f))
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
		active._blocks[i]->applyParticle(particleTime, _particleInfo[index], _data[index]);

	stepParticle(index, EMIT_STEP);
	// Do some more calcs (e.g. texture assignments)..
}

void Emission::updateParticles()
{
	// Update particels
	bool looped = isLooped();
	size_t end = looped ? _particleInfo.size() : _cycleEnd;
	for (size_t i = _cycleBegin; i < end; i++)
		updateParticle(i);
	// Update the cycled list if necesary
	if (looped)
	{
		for (size_t i = 0; i < _cycleEnd; i++)
			updateParticle(i);
	}
}
void Emission::spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime)
{
	float duration = _emitter->_particleLink ?
		_emitter->_particleLink->_time.duration() :
		PARTICLE_DEFAULT_DUR;
	// Emitt n particles (interpolate particle emission: n/frame)
	float n = glm::mix(spawner->_params._initAmount, spawner->_params._endAmount, (blockTime + EMIT_STEP*0.5) / duration);
	float dTime = EMIT_STEP / (n + 1.f);
	// Lazy solution, emitted particles is floored.
	// Remainder needs to be stored for next update so the number of particles emitted is correct...
	for (float i = 0; i < n; i++) 
	{
		InitialEmissionParams &param = spawner->_params;
		Particle p;
		p._spawnTime = _effect->_time + dTime * i;
		p._initSize = glm::mix(param._minSize, param._maxSize, randomFloat());
		p._initDir = param._emitDir;

		GPUParticle gpuP;
		gpuP._rotation = glm::mix(param._minRotation, param._maxRotation, randomFloat());
		gpuP._position = param._emitOrigin;

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
		spawnParticle((SpawnBlock*)spawners._blocks[i], list, spawners._blocks[i]->_time.toRelative(emitterTime));
}

