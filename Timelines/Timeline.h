#pragma once
#include <vector>
#include "Block.h"
#include "Channel.h"
#include "TimelineType.h"

/* Maximum number of channels supported in a timeline
*/
static const unsigned int MAX_CHANNELS = 10;
/*	Container for blocks active in a timeline at a time instance.
*	Size is static but number of blocks is limited by the number of channels!
*/
struct BlockList
{
	Block* _blocks[MAX_CHANNELS];
	unsigned int _size;

	BlockList()
	 : _size(0)
	{}

	void push(Block* b)
	{
		_blocks[_size] = b;
		_size++;
	}

	void remove(unsigned int index)
	{
		if(index != _size - 1)
			std::swap(_blocks[index], _blocks[_size - 1]);
		_size--;
	}
};

/* Timelines containing the params for the particle effect(s).
*/
class Timeline
{
public:
	
	type::Timeline _type;
	/* If emitter timeline, this is the linked particle (can be NULL) */
	Timeline *_particleLink;
	/* Start and endtime of the timeline in absolute values related to parented timelines
	*/
	float _startTime, _endTime;
	/* Get the duration of the timeline in seconds. */
	float duration() { return _endTime - _startTime; }
	/* Convert parent time parameter to relative time for the timeline. */
	float toRelative(float parentTime) { return parentTime - _startTime; }
	/* Channels containing the blocks controlling the params. */
	std::vector<Channel*> _channel;

	Timeline(type::Timeline type);
	~Timeline();

	void addBlock(Block *b, unsigned int channel);

	/* Fetch possible blocks affecting the particle effect at the time relative to the timeline
	*/
	BlockList fetchBlocks(float relativeTime);
};

