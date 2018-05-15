#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

/* Constant force
*/
class GravityBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _forceDir;
	float _gravity;

	GravityBlock(TimeInterval t);
	virtual ~GravityBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);
};

