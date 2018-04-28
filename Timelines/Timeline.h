#pragma once
#include <vector>
#include "Block.h"
#include "Channel.h"
#include "TimelineType.h"

/* Timelines containing the params for the particle effect(s).
*/
class Timeline
{
public:
	type::Timeline _type;
	/* If emitter timeline, this is the linked particle (can be NULL) */
	Timeline *_particleLink;
	/* Channels containing the blocks controlling the params. */
	std::vector<Channel*> _channel;

	Timeline(type::Timeline type);
	~Timeline();
};

