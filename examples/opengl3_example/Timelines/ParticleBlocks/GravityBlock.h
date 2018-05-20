#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

/* Accelerate toward a point
*/
class GravityBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _gravityPoint;
	// Constant force -> gravity point
	float _gravity;

	GravityBlock(TimeInterval t);
	GravityBlock(TimeInterval t, glm::vec3 gravityPoint, float constantForce);
	virtual ~GravityBlock();

	virtual void applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties(ImVec2 pos, ImVec2 size);
};

