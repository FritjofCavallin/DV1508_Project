#include "Channel.h"



Channel::Channel()
{
}


Channel::~Channel()
{
	for (auto b : _data)
		delete b;
}
