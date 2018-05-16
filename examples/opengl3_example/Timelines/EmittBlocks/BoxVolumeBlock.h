#pragma once
#include "../Block.h"
#include "glm/vec3.hpp"

class BoxVolumeBlock :
	public Block
{
public:

	/* Parameters
	*/
	glm::vec3 _volumeSize;

	BoxVolumeBlock(TimeInterval t);
	virtual ~BoxVolumeBlock();

	virtual void applyEmitter(Particle &part, GPUParticle &gpuPart);

	virtual void DrawProperties();
};

