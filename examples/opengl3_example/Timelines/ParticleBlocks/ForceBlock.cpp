#include "ForceBlock.h"
#include "../../Particles/Constants.h"


ForceBlock::ForceBlock(TimeInterval t)
	: Block(t, type::Particle)
{
}


ForceBlock::~ForceBlock()
{
}

void ForceBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _forceApplied *  EMIT_STEP / _time.duration();
}