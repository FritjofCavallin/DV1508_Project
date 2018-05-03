#include "Block.h"



Block::Block(TimeInterval t)
	: _time(t)
{
}


Block::~Block()
{
}

bool Block::overlaps(Block* other)
{
	return !(other->_time._startTime <= _time._startTime && other->_time._endTime <= _time._startTime ||
		other->_time._endTime >= _time._endTime && other->_time._startTime >= _time._endTime);
}
