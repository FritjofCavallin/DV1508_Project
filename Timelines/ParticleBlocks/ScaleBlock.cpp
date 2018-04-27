#include "ScaleBlock.h"



ScaleBlock::ScaleBlock()
{
}


ScaleBlock::~ScaleBlock()
{
}

void ScaleBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._size.x *= glm::mix(_scaleBegin.x, _scaleEnd.x, toRelative(emittTime));
	gpuPart._size.y *= glm::mix(_scaleBegin.y, _scaleEnd.y, toRelative(emittTime));
}