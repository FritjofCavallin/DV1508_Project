#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

class ForceBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _forceDir;
	float _forceApplied;

	ForceBlock();
	virtual ~ForceBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() { return type::Particle; }
};

