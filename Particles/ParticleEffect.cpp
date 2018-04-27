#include "ParticleEffect.h"
#include "Emissions.h"
#include "Timelines/EffectBlock.h"

ParticleEffect::ParticleEffect()
	: _timeline(nullptr), _time(0.f), _loopTime(MAX_DURATION)
{
}

ParticleEffect::ParticleEffect(Timeline *timeline)
	: _timeline(timeline), _time(0.f), _loopTime(MAX_DURATION)
{
}


ParticleEffect::~ParticleEffect()
{
}

void ParticleEffect::incrementTime(float step)
{
	_time = std::fmodf(_time + step, _loopTime);
}

void ParticleEffect::update()
{
	if (!_timeline) return;

	float emittTime = std::fmodf(_time, _timeline->duration());
	BlockList list = _timeline->fetchBlocks(emittTime);

	for (unsigned int i = 0; i < list._size; i++)
	{
		Timeline *emitter = reinterpret_cast<EffectBlock*>(list._blocks[i])->_emitter;

		Emission *e;
		auto it = _emitters.find(emitter);
		if (it == _emitters.end())
			e = it->second;
		else
		{
			e = new Emission(this, emitter);
			_emitters[emitter] = e;
		}

		e->spawnParticles(emittTime);
	}

	incrementTime(EMIT_STEP);
	emittTime = std::fmodf(_time, _timeline->duration());

	for (auto e : _emitters)
		e.second->updateParticles(emittTime);
}