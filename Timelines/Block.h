#pragma once

#include "TimelineType.h"

/* Block in the timeline that affects a certain param in the effect. 
*/
class Block
{
public:

	Block();
	virtual ~Block();

	/* The timeline type the block is associated with
	*/
	virtual type::Timeline typeFit() = 0;
};

