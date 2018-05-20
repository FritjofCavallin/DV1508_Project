#include <iostream>

#include "Timeline.h"

Timeline::Timeline(type::Timeline type, const std::string &name, TimeInterval t)
	: _type(type), _name(name), _particleLink(nullptr), _timeTotal(t), _timeShown(t)
{
	_channel.push_back(new Channel());
}


Timeline::~Timeline()
{
	for (auto c : _channel)
		delete c;
}



bool Timeline::addBlock(Block *b, unsigned int channel, bool insertChannel)
{
	if (channel >= MAX_CHANNELS) // Channel index to large (see MAX_CHANNEL const)
	{
		std::cerr << "Tried to add a block to a channel index greater than MAX_CHANNELS\n";
		return false; 
	}
	if (b->typeFit() != _type) // Wrong timeline for block
	{
		std::cerr << "Tried to add a block to a non-matching timeline\n";
		return false; 
	}
	if (!(_timeTotal._startTime <= b->_time._startTime && _timeTotal._startTime <= b->_time._endTime &&
		_timeTotal._endTime >= b->_time._startTime && _timeTotal._endTime >= b->_time._endTime))
	{
		std::cerr << "Block time interval is not contained within timeline time interval\n";
		return false;
	}

	if (channel >= _channel.size())
	{
		channel = _channel.size();
		_channel.push_back(new Channel());
	}

	if (insertChannel && _channel.size() < MAX_CHANNELS)
	{
		auto it = _channel.begin();
		for (unsigned int i = 0; i < channel; ++i)
			++it;
		_channel.insert(it, new Channel());

		_channel[channel]->_data.push_back(b);
	}
	else
	{
		// Make space for the placed block
		std::vector<Block*> displacedBlocks;
		for (unsigned int i = 0; i < _channel[channel]->_data.size(); ++i)
		{
			Block* other = _channel[channel]->_data[i];
			if (b->contains(other) || other->contains(b))
			{
				// Displace other
				displacedBlocks.push_back(other);
			}
			// If the blocks are partially overlapping, cut the other blocks to make space for b
			else if (b->overlaps(other))
			{
				if (other->_time._startTime < b->_time._startTime && other->_time._endTime > b->_time._startTime)
				{
					// If correcting other block width would make it shorter than allowed
					if (b->_time._startTime - other->_time._startTime < _channel[channel]->minBlockDuration)
					{
						// Displace other
						displacedBlocks.push_back(other);
					}
					else
					{
						other->_time._endTime = b->_time._startTime;
					}
				}
				if (other->_time._endTime > b->_time._endTime && other->_time._startTime < b->_time._endTime)
				{
					// If correcting other block width would make it shorter than allowed
					if (other->_time._endTime - b->_time._endTime < _channel[channel]->minBlockDuration)
					{
						// Displace other
						displacedBlocks.push_back(other);
					}
					else
					{
						other->_time._startTime = b->_time._endTime;
					}
				}
			}
		}

		// Remove displaced blocks from channel
		for (Block* d : displacedBlocks)
		{
			removeBlock(d, false);
		}

		// Insert b
		_channel[channel]->_data.push_back(b);

		// Handle displaced blocks
		if (displacedBlocks.size() > 0)
		{
			if (_channel.size() < MAX_CHANNELS)
			{
				if (channel == _channel.size() - 1)
				{
					_channel.push_back(new Channel());

					// Place in next channel
					for (Block* b : displacedBlocks)
					{
						_channel[channel + 1]->_data.push_back(b);
					}
				}
				else
				{
					// Check if all blocks fit in next channel
					bool allFit = true;
					for (unsigned int i = 0; i < displacedBlocks.size(); ++i)
					{
						if (!_channel[channel + 1]->blockFits(displacedBlocks[i]))
						{
							allFit = false;
							break;
						}
					}

					// If all blocks fit in next channel, place them there
					if (allFit)
					{
						for (Block* b : displacedBlocks)
						{
							_channel[channel + 1]->_data.push_back(b);
						}
					}
					// Else, create new channel and place the blocks there
					else
					{
						auto it = _channel.begin();
						for (unsigned int i = 0; i < channel; ++i)
							++it;
						++it;	// One extra step, to add the new channel after the desired one, not before
						_channel.insert(it, new Channel());

						// Place in next channel
						for (Block* b : displacedBlocks)
						{
							_channel[channel + 1]->_data.push_back(b);
						}
					}
				}
			}
			else
			{
				fitDisplacedBlocks(displacedBlocks);
			}

		}
	}

	channelCleanup();

	return true;
}

Block* Timeline::removeBlock(int channelIndex, int blockIndex, bool doCleanup)
{
	Block* ret = _channel[channelIndex]->_data[blockIndex];

	auto it = _channel[channelIndex]->_data.begin();
	for (int i = 0; i < blockIndex; ++i)
		++it;

	_channel[channelIndex]->_data.erase(it);

	if (doCleanup)
		channelCleanup();

	return ret;
}


Block* Timeline::removeBlock(Block* block, bool doCleanup)
{
	for (unsigned int c = 0; c < _channel.size(); ++c)
	{
		for (unsigned int b = 0; b < _channel[c]->_data.size(); ++b)
		{
			if (_channel[c]->_data[b] == block)
			{
				return removeBlock(c, b, doCleanup);
			}
		}
	}
	return nullptr;
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
	// Count empty channels
	int emptyChannels = 0;
	for (unsigned int c = 0; c < _channel.size(); ++c)
	{
		if (_channel[c]->isEmpty())
		{
			emptyChannels++;
		}
	}

	if (emptyChannels == 0 && _channel.size() < MAX_CHANNELS)
	{
		_channel.push_back(new Channel());
	}
	else
	{
		for (int i = 0; i < emptyChannels - 1; ++i)
		{
			auto it = _channel.begin();
			while (it != _channel.end())
			{
				if ((*it)->isEmpty())
				{
					_channel.erase(it);
					break;
				}

				++it;
			}
		}
	}
}

void Timeline::fitDisplacedBlocks(std::vector<Block*>& displacedBlocks)
{
	for (Block* b : displacedBlocks)
	{
		bool inserted = false;
		for (Channel* c : _channel)
		{
			if (c->blockFits(b))
			{
				c->_data.push_back(b);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			delete b;
	}
}
