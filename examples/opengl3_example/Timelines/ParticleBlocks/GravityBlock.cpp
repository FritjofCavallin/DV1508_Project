#include "GravityBlock.h"
#include "../../Other/Constants.h"


GravityBlock::GravityBlock(TimeInterval t)
	: Block(t, type::Particle), _gravityPoint(0,0,0), _gravity(9.82f)
{
}
GravityBlock::GravityBlock(TimeInterval t, glm::vec3 gravityPoint, float constantForce)
	: Block(t, type::Particle), _gravityPoint(gravityPoint), _gravity(constantForce)
{
}


GravityBlock::~GravityBlock()
{
}

void GravityBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	// Accelerate toward the gravity point
	part._velocity += glm::normalize(_gravityPoint - gpuPart._position) * _gravity *  EMIT_STEP;
}