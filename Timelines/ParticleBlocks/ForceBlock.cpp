#include "ForceBlock.h"
#include "Particles/ParticleEffect.h"


ForceBlock::ForceBlock()
{
}


ForceBlock::~ForceBlock()
{
}

void ForceBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _forceApplied *  EMIT_STEP / duration();
}