#include <iostream>

#include "Timeline.h"

Timeline::Timeline(type::Timeline type, const std::string &name, TimeInterval t)
	: _type(type), _name(name), _particleLink(nullptr), _time(t)
{
		_channel.push_back(new Channel());
}


Timeline::~Timeline()
{
	for (auto c : _channel)
		delete c;
}



bool Timeline::addBlock(Block *b, unsigned int channel)
{
	if (channel >= _channel.size()) // Channel index to large (see MAX_CHANNEL const)
	{
		std::cerr << "Tried to add a block to a channel index greater than MAX_CHANNELS\n";
		return false; 
	}
	if (b->typeFit() != _type) // Wrong timeline for block
	{
		std::cerr << "Tried to add a block to a non-matching timeline\n";
		return false; 
	}
	if (!(_time._startTime <= b->_time._startTime && _time._startTime <= b->_time._endTime &&
		_time._endTime >= b->_time._startTime && _time._endTime >= b->_time._endTime))
	{
		std::cerr << "Block time interval is not contained within timeline time interval\n";
		return false;
	}

	bool success = false;
	// Check for overlapping blocks in same channel
	if (_channel[channel]->blockFits(b))
	{
		_channel[channel]->_data.push_back(b);
		success = true;
	}
	else
	{
		// First, try to create a new channel after the desired one
		if (_channel.size() < MAX_CHANNELS)
		{
			auto it = _channel.begin();
			for (int i = 0; i < channel; ++i)
				++it;
			++it;	// One extra step, to add the new channel after the desired one, not before

			_channel.insert(it, new Channel());

			// Insert block
			_channel[channel + 1]->_data.push_back(b);
			success = true;
		}
		// Lastly, check if block fits within other existing channels
		else
		{
			for (Channel* c : _channel)
			{
				if (c->blockFits(b))
				{
					c->_data.push_back(b);
					success = true;
					break;
				}
			}
		}
	}

	channelCleanup();

	return success;
}

Block* Timeline::removeBlock(int channelIndex, int blockIndex)
{
	Block* ret = _channel[channelIndex]->_data[blockIndex];

	auto it = _channel[channelIndex]->_data.begin();
	for (int i = 0; i < blockIndex; ++i)
		++it;

	_channel[channelIndex]->_data.erase(it);

	channelCleanup();

	return ret;
}


Block* Timeline::removeBlock(Block* block)
{
	for (int c = 0; c < _channel.size(); ++c)
	{
		for (int b = 0; b < _channel[c]->_data.size(); ++b)
		{
			if (_channel[c]->_data[b] == block)
			{
				return removeBlock(c, b);
			}
		}
	}
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

void Timeline::channelCleanup()
{
	// Remove empty channels in the middle of the vector
	for (int c = 0; c < _channel.size() - 1; ++c)
	{
		if (_channel[c]->isEmpty())
		{
			auto it = _channel.begin();
			for (int i = 0; i < c; ++i)
				++it;

			_channel.erase(it);
		}
	}

	// Ensure there is an empty channel at the end of the vector, as long as there is space
	if (!_channel[_channel.size() - 1]->isEmpty() && _channel.size() < MAX_CHANNELS)
	{
		_channel.push_back(new Channel());
	}
}
