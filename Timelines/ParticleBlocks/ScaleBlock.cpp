#include "ScaleBlock.h"



ScaleBlock::ScaleBlock(TimeInterval t)
	: Block(t)
{
}


ScaleBlock::~ScaleBlock()
{
}

void ScaleBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._size.x *= glm::mix(_scaleBegin.x, _scaleEnd.x, _time.toRelative(emittTime));
	gpuPart._size.y *= glm::mix(_scaleBegin.y, _scaleEnd.y, _time.toRelative(emittTime));
}