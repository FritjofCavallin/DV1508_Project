#include "ScaleBlock.h"



ScaleBlock::ScaleBlock(TimeInterval t)
	: Block(t, type::Particle)
{
}


ScaleBlock::~ScaleBlock()
{
}

void ScaleBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._size *= glm::mix(_scaleBegin, _scaleEnd, _time.toRelativeNor(emittTime));
}