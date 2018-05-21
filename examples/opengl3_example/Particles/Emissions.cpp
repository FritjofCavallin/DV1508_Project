#include "Emissions.h"
#include "ParticleEffect.h"
#include "../Other/RandFunction.h"
#include "glm/geometric.hpp"
#include "../Other/Constants.h"
#include <algorithm>
#include "../Timelines/EmittBlocks/TextureBlock.h"

Emission::Emission(ParticleEffect* effect, Timeline *emitter, ParticleShader *shader)
	: _emitter(emitter), _shader(shader), _particleInfo(PARTICLES_EMITTED_MAX), _data(PARTICLES_EMITTED_MAX), _effect(effect),
	_remainder(0.f), _cycleBegin(0), _cycleEnd(0), _bufCycle(0)
{
	_shadeBuffers[0] = shader->genBuffer(PARTICLES_EMITTED_MAX);
	_shadeBuffers[1] = shader->genBuffer(PARTICLES_EMITTED_MAX);
	for(int i = 0; i < 4; i++){
		_texActive[i] = 0;
		_texSlots[i] = 0;
	}
}


Emission::~Emission()
{
	_shadeBuffers[0].destroy();
	_shadeBuffers[1].destroy();
}

void Emission::bindTextures()
{
	for (int i = 0; i < 4; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		GLuint texInd = _texActive[i] ? _texSlots[i] : _shader->defaultTex;
		glBindTexture(GL_TEXTURE_2D, texInd);
		//_texActive[i] = false;
	}
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
	//Bind textures:
	checkGLError();
	
	bindTextures();
	
	checkGLError();
	

	_shadeBuffers[_bufCycle].draw();
	checkGLError();
}

void Emission::stepParticle(unsigned int index, float timeStep)
{
	_data[index]._position += timeStep * _particleInfo[index]._velocity;
}

bool Emission::isLooped() { return _cycleEnd < _cycleBegin; }
void Emission::incrementCycleEnd() { _cycleEnd++; if (_cycleEnd == _particleInfo.size()) _cycleEnd = 0; }
void Emission::incrementCycleBegin() { _cycleBegin++; if (_cycleBegin == _particleInfo.size()) _cycleBegin = 0; }

size_t Emission::numActive()
{
	return _cycleEnd < _cycleBegin ?
		_particleInfo.size() - _cycleBegin + _cycleEnd : //Looped count
		_cycleEnd - _cycleBegin;
}

bool Emission::active(unsigned int index) { return _particleInfo[index].dead(_effect->elapsedSince(_particleInfo[index]._spawnTime), _emitter->_particleLink); }


void Emission::updateParticle(unsigned int index)
{
	float pTime = _effect->elapsedSince(_particleInfo[index]._spawnTime);
	if (_particleInfo[index].update(_data[index], pTime, _emitter->_particleLink))
		incrementCycleBegin();
	else
		stepParticle(index, EMIT_STEP);
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
void Emission::spawnParticle(SpawnBlock *spawner, BlockList &active, float blockTime, float deltaT)
{
	float duration = _emitter->_particleLink ?
		_emitter->_particleLink->_timeTotal.duration() :
		PARTICLE_DEFAULT_DUR;

	float lerp = std::fmaxf(0, (blockTime - deltaT * 0.5f) / duration);

	// Emitt n particles (cheap interpolation over particle emission: Total/n)
	//float n = glm::mix(spawner->_params._initAmount, spawner->_params._endAmount, lerp) / duration * deltaT;
	_remainder = glm::mix(spawner->_params._initAmount, spawner->_params._endAmount, lerp) * deltaT + _remainder;
	int N = (int)_remainder;
	_remainder = _remainder - N;

	float dTime = deltaT / (N + 1.f);
	// Lazy solution, emitted particles is floored.
	// Remainder needs to be stored for next update so the number of particles emitted is correct...
	for (int i = 1; i <= N; i++)
	{
		InitialEmissionParams &param = spawner->_params;
		Particle p;
		float timeOffset = dTime * (N - i);
		p.init(param, _effect->_time - timeOffset);

		// Lerp initial position depending on initial velocity
		GPUParticle gpuP;
		p._velocity = glm::mix(param._minForce, param._maxForce, randomFloat()) * p._initDir;
		gpuP._position = param._emitOrigin + p._initDir * p._velocity * timeOffset;

		gpuP._rotation = glm::mix(param._minRotation, param._maxRotation, randomFloat());

		gpuP._texArea[0] = 0;
		gpuP._texArea[1] = 0;
		gpuP._texArea[2] = 0;
		gpuP._texArea[3] = 0;

		// Apply emitter blocks
		for (unsigned int ii = 0; ii < active._size; ii++)
			active._blocks[ii]->applyEmitter(p, gpuP);


		// Add new particle
		_particleInfo[_cycleEnd] = p;
		_data[_cycleEnd] = gpuP;
		incrementCycleEnd();
	}
}
void Emission::spawnParticles(float emitterTime, float deltaT)
{
	BlockList list = _emitter->fetchBlocks(emitterTime);
	BlockList spawners;

	for (unsigned int i = 0; i < list._size; i++)
	{
		SpawnBlock *b = dynamic_cast<SpawnBlock*> (list._blocks[i]);
		TextureBlock *t = dynamic_cast<TextureBlock*> (list._blocks[i]);
		if (b != NULL)
		{
			spawners.push(b);
			list.remove(i--);
		}
		else if (t != NULL)
		{
			list.remove(i--);
			_texSlots[t->_texSlot] = t->gTextureID;
			_texActive[t->_texSlot] = true;
		}
	}
	for (unsigned int i = 0; i < spawners._size; i++)
	{
		SpawnBlock *b = reinterpret_cast<SpawnBlock*>(spawners._blocks[i]);
		spawnParticle(b, list, b->_time.toRelative(emitterTime), deltaT);
	}
}




Timeline* Emission::getEmitter() { return _emitter; }
GPUParticle& Emission::operator[](unsigned int index) { return _data[index]; }
/* Get the index of the last particle. */
unsigned int Emission::last() { return _cycleEnd + (_cycleEnd > 0 ? -1 : _data.size() - 1); }

