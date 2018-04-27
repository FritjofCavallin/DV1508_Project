#include "Timeline.h"



Timeline::Timeline(type::Timeline type)
	: _type(type), _particleLink(nullptr), _startTime(0.f), _endTime(3.f), _channel(MAX_CHANNELS)
{

	for (size_t i = 0; i < _channel.size(); i++)
		_channel[i] = new Channel();
}


Timeline::~Timeline()
{
}



BlockList Timeline::fetchBlocks(float relativeTime)
{
	BlockList list;
	// Append blocks to the block list
	for (Channel* c : _channel)
	{
		for (Block *b : c->_data)
		{
			if (b->_startTime >= relativeTime && b->_endTime < relativeTime)
				list.push(b);
		}
	}
	return list;
}