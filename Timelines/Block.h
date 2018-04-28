#pragma once

#include "TimelineType.h"
#include "Particles/Particle.h"
#include "TimeInterval.h"

/* Block in the timeline that affects a certain param in the effect. 
*/
class Block
{
public:

	Block(TimeInterval t);
	virtual ~Block();

	/* Time interval in absolute values related to parented timelines. */
	TimeInterval _time;

	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() = 0;


	virtual void applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart) {};
	virtual void applyEmitter(Particle &part, GPUParticle &gpuPart) {};
};

