#include "RotationBlock.h"
#include "../../Other/Constants.h"


RotationBlock::RotationBlock(TimeInterval t)
	: Block(t, type::Particle), _angVelocityBegin(3.14f/20.f), _angVelocityEnd(3.14f / 3.f)
{
	visualName = "Rotation";
	desc = "Rotate the particle quad";
}


RotationBlock::~RotationBlock()
{
}

void RotationBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._rotation += glm::mix(_angVelocityBegin, _angVelocityEnd, _time.toRelativeNor(emittTime)) * EMIT_STEP;
}

void RotationBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

}