#pragma once
#include <vector>
#include "Block.h"
#include "Channel.h"

/* Timelines containing the params for the particle effect(s).
*/
class Timeline
{
public:
	enum Type
	{
		Effect,
		Emitter,
		Particle
	};
	Type _type;
	/* If emitter timeline, this is the linked particle (can be NULL) */
	Timeline *_particleLink;
	/* Channels containing the blocks controlling the params. */
	std::vector<Channel*> _channel;

	Timeline(Type type);
	~Timeline();
};

