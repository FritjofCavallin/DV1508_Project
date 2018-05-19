#include "Block.h"



Block::Block(TimeInterval t, type::Timeline type)
	: _time(t), _type(type)
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

bool Block::contains(Block* other)
{
	return _time._startTime <= other->_time._startTime && _time._endTime >= other->_time._endTime;
}
