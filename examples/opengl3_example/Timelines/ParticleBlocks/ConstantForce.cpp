#include "ConstantForce.h"
#include "../../Other/Constants.h"


ConstantForce::ConstantForce(TimeInterval t)
	: Block(t, type::Particle), _forceDir(0,-1,0), _gravity(9.82f)
{
	visualName = "Constant\n Force";
	desc = "Apply a constant force";
}


ConstantForce::~ConstantForce()
{
}

void ConstantForce::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _gravity *  EMIT_STEP;
}

void ConstantForce::DrawProperties(){

}