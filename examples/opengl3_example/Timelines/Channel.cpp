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

Channel::Channel()
{
}


Channel::~Channel()
{
	for (auto b : _data)
		delete b;
}
