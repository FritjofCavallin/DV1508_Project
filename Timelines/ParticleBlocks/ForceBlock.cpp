#include "ForceBlock.h"
#include "Particles/ParticleEffect.h"


ForceBlock::ForceBlock(TimeInterval t)
	: Block(t)
{
}


ForceBlock::~ForceBlock()
{
}

void ForceBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _forceApplied *  EMIT_STEP / _time.duration();
}