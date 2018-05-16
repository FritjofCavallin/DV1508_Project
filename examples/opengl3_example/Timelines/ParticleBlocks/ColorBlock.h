#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

class ColorBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec4 _colorBegin, _colorEnd;

	ColorBlock(TimeInterval t);
	virtual ~ColorBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties();
};

