#include "ForceBlock.h"
#include "../../Other/Constants.h"


ForceBlock::ForceBlock(TimeInterval t)
	: Block(t, type::Particle), _gravityPoint(0,1,0), _force(10.f)
{
}

ForceBlock::ForceBlock(TimeInterval t, glm::vec3 forceDir, float force)
	: Block(t, type::Particle), _gravityPoint(forceDir), _force(force)
{
}

ForceBlock::~ForceBlock()
{
}

void ForceBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _gravityPoint * _force *  EMIT_STEP / _time.duration();
}