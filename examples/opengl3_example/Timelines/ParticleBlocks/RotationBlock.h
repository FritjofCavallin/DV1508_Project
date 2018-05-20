#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

class RotationBlock :
	public Block
{
public:

	/* Parameters
	*/
	float _angVelocityBegin, _angVelocityEnd;

	RotationBlock(TimeInterval t);
	virtual ~RotationBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties(ImVec2 pos, ImVec2 size);
};

