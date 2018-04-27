#pragma once

#include "TimelineType.h"
#include "Particles/Particle.h"

/* Block in the timeline that affects a certain param in the effect. 
*/
class Block
{
public:

	Block();
	virtual ~Block();

	/* Start and endtime of the block in absolute values related to it's parent timeline 
	*/
	float _startTime, _endTime;
	/* Get the duration of the block in seconds. */
	float duration() { return _endTime - _startTime; }
	/* Convert parent time parameter to relative time for the block. */
	float toRelative(float parentTime) { return parentTime - _startTime; }

	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() = 0;


	virtual void applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart) {};
	virtual void applyEmitter(Particle &part, GPUParticle &gpuPart) {};
};

