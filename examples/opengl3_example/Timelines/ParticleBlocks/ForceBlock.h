#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

/* Force applied over time
*/
class ForceBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _gravityPoint;
	float _force;

	ForceBlock(TimeInterval t);
	ForceBlock(TimeInterval t, glm::vec3 forceDir, float force);
	virtual ~ForceBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties();
};

