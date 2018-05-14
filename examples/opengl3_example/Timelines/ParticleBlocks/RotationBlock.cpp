#include "RotationBlock.h"
#include "../../Particles/Constants.h"


RotationBlock::RotationBlock(TimeInterval t)
	: Block(t, type::Particle), _angVelocityBegin(3.14/20.f), _angVelocityEnd(3.14 / 3.f)
{
}


RotationBlock::~RotationBlock()
{
}

void RotationBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._rotation += glm::mix(_angVelocityBegin, _angVelocityEnd, _time.toRelativeNor(emittTime)) * EMIT_STEP;
}