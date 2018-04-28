#pragma once
#include "Block.h"
#include "glm/vec3.hpp"
#include "Timeline.h"

class EffectBlock :
	public Block
{
public:

	/* Parameters
	*/
	Timeline *_emitter;

	EffectBlock(Timeline *emitter, TimeInterval t);
	virtual ~EffectBlock();
	
	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() { return type::Effect; }
};

