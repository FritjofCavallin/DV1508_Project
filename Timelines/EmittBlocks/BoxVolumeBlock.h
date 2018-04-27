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

	BoxVolumeBlock();
	virtual ~BoxVolumeBlock();

	virtual void applyEmitter(Particle &part, GPUParticle &gpuPart);

	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() { return type::Particle; }
};

