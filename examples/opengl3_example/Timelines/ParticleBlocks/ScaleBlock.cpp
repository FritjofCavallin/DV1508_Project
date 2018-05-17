#include "ScaleBlock.h"



ScaleBlock::ScaleBlock(TimeInterval t)
	: Block(t, type::Particle)
{
	visualName = "Scale";
	desc = "Change size of the particle";
}


ScaleBlock::~ScaleBlock()
{
}

void ScaleBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._size *= glm::mix(_scaleBegin, _scaleEnd, _time.toRelativeNor(emittTime));
}

void ScaleBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

}