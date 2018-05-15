#pragma once
#include <vector>
#include "Block.h"
#include "Channel.h"
#include "TimelineType.h"
#include "TimeInterval.h"
#include "../Other/Constants.h"

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
	/* Name identifier*/
	std::string _name;
	/* If emitter timeline, this is the linked particle (can be NULL) */
	Timeline *_particleLink;

	/* Time interval in absolute values related to parented timelines */
	TimeInterval _time;

	Block* _movingBlock = nullptr;
	

	/* Channels containing the blocks controlling the params. */
	std::vector<Channel*> _channel;

	Timeline(type::Timeline type, const std::string &name, TimeInterval t);
	~Timeline();

	// Returns true on success, false otherwise
	// Note that the block might be placed on another channel if it can't fit in the specified one
	// If insertChannel == true, a new channel is always inserted if possible
	bool addBlock(Block *b, unsigned int channel, bool insertChannel = false);

	// Removes and returns block blockIndex of channel channelIndex
	Block* removeBlock(int channelIndex, int blockIndex, bool doCleanup = true);

	// Removes and returns the specified block, if found
	Block* removeBlock(Block* block, bool doCleanup = true);

	/* Fetch possible blocks affecting the particle effect at the time relative to the timeline
	*/
	BlockList fetchBlocks(float relativeTime);

private:
	// Ensures there is an empty channel at the end of the _channel vector, and removes other empty channels
	void channelCleanup();
};

