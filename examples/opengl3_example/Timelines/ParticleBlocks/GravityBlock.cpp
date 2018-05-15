#include "GravityBlock.h"
#include "../../Other/Constants.h"


GravityBlock::GravityBlock(TimeInterval t)
	: Block(t, type::Particle), _forceDir(0,-1,0), _gravity(9.82f)
{
}


GravityBlock::~GravityBlock()
{
}

void GravityBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _gravity *  EMIT_STEP;
}