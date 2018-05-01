#include <iostream>

#include "Channel.h"

bool Channel::isEmpty()
{
	return _data.size() == 0;
}

bool Channel::blockFits(Block* block)
{
	for (Block* b : _data)
		if (b->overlaps(block))
			return false;

	return true;
}

void Channel::correctBlockDuration(Block* draggedBlock, TimeInterval timelineExtent, bool left)
{
	if (std::find(_data.begin(), _data.end(), draggedBlock) == _data.end())
	{
		std::cerr << "Attempted to call correctBlockDuration() with a block not contained in the channel called";
	}

	for (int i = 0; i < _data.size(); ++i)
	{
		if (_data[i] == draggedBlock)
			continue;

		if (left)
		{
			if (draggedBlock->_time._startTime < _data[i]->_time._endTime && draggedBlock->_time._endTime >= _data[i]->_time._endTime)
				draggedBlock->_time._startTime = _data[i]->_time._endTime;
		}
		else
		{
			if (draggedBlock->_time._endTime > _data[i]->_time._startTime && draggedBlock->_time._startTime <= _data[i]->_time._startTime)
				draggedBlock->_time._endTime = _data[i]->_time._startTime;
		}
	}

	if (draggedBlock->_time._startTime < timelineExtent._startTime)
		draggedBlock->_time._startTime = timelineExtent._startTime;

	if (draggedBlock->_time._endTime > timelineExtent._endTime)
		draggedBlock->_time._endTime = timelineExtent._endTime;

	if (left)
	{
		if (draggedBlock->_time._startTime > draggedBlock->_time._endTime)
			draggedBlock->_time._startTime = draggedBlock->_time._endTime;
	}
	else
	{
		if (draggedBlock->_time._endTime < draggedBlock->_time._startTime)
			draggedBlock->_time._endTime = draggedBlock->_time._startTime;
	}
}

Channel::Channel()
{
}

Channel::~Channel()
{
	for (auto b : _data)
		delete b;
}
