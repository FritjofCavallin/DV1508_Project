#include "ParticleEffect.h"
#include "Emissions.h"
#include "../Timelines/EffectBlock.h"
#include <sstream>

ParticleEffect::ParticleEffect()
	: _timeline(nullptr), _time(0.f), _loopTime(MAX_DURATION)
{
	_shader.load();
}

ParticleEffect::ParticleEffect(Timeline *timeline)
	: _timeline(timeline), _time(0.f), _loopTime(MAX_DURATION)
{
	_shader.load();
}

ParticleEffect::~ParticleEffect()
{
	for (auto e : _emitters)
		delete e.second;
}

void ParticleEffect::incrementTime(float step)
{
	_time = std::fmodf(_time + step, _loopTime);
}

void ParticleEffect::update()
{
	if (!_timeline) return;

	float effectTime = std::fmodf(_time, _timeline->_time.duration());
	BlockList list = _timeline->fetchBlocks(effectTime);

	// For every active emitter: spawn particles
	for (unsigned int i = 0; i < list._size; i++)
	{
		EffectBlock *eBlock = reinterpret_cast<EffectBlock*>(list._blocks[i]);
		Timeline *emitter = eBlock->_emitter;

		Emission *e;
		auto it = _emitters.find(eBlock);
		if (it != _emitters.end())
			e = it->second;
		else
		{
			e = new Emission(this, emitter, &_shader);
			_emitters[eBlock] = e;
		}
		// Remap time from effect time to time on the emitter scale:
		float timeRemap = emitter->_time.duration() / eBlock->_time.duration();
		float emitterTime = (effectTime - eBlock->_time._startTime)  /  eBlock->_time.duration() * emitter->_time.duration();
		e->spawnParticles(emitterTime, EMIT_STEP * timeRemap);
	}

	// Increment timestep after particles are spawned,
	// new particels will take a constant step anyway
	incrementTime(EMIT_STEP);

	// Update particles
	for (auto e : _emitters)
		e.second->updateParticles();
}

void ParticleEffect::render(Camera *cam)
{
	_shader.assignGlobalUniforms(cam);
	for (auto e : _emitters)
		e.second->render();
}

std::string ParticleEffect::getStatus()
{
	std::stringstream ss;
	ss << "-----------\n";
	ss << "Effect time: " << _time << '\n';
	ss << "-----------\n";
	for (auto e : _emitters)
	{
		ss << e.second->_emitter->_name << '\n';
		ss << "Particles: \t\t" << e.second->numActive() << '\n';
	}
	ss << '\n';
	return ss.str();
}