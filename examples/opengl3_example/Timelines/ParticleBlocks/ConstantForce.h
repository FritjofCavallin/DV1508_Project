#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

/* Constant force
*/
class ConstantForce :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _forceDir;
	float _gravity;

	ConstantForce(TimeInterval t);
	virtual ~ConstantForce();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties();
};

