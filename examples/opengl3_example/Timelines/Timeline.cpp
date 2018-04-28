#include "Timeline.h"



Timeline::Timeline(type::Timeline type, const std::string &name, TimeInterval t)
	: _type(type), _name(name), _particleLink(nullptr), _time(0.f, 3.f), _channel(MAX_CHANNELS)
{

	for (size_t i = 0; i < _channel.size(); i++)
		_channel[i] = new Channel();
}


Timeline::~Timeline()
{
}



void Timeline::addBlock(Block *b, unsigned int channel)
{
	if (channel >= _channel.size())
		return; // Channel index to large (see MAX_CHANNEL const)
	if (b->typeFit() != _type)
		return; //Wrong timeline for block

	//Should be inserted properly!
	_channel[channel]->_data.push_back(b);
}


BlockList Timeline::fetchBlocks(float relativeTime)
{
	BlockList list;
	// Append blocks to the block list
	for (Channel* c : _channel)
	{
		for (Block *b : c->_data)
		{
			if (b->_time._startTime <= relativeTime && relativeTime < b->_time._endTime)
				list.push(b);
		}
	}
	return list;
}