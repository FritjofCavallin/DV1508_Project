#pragma once
#include "Block.h"
#include <vector>

/* Timeline channel
*/
class Channel
{
public:

	std::vector<Block*> _data; // vector = simple solution, could be improved if needed

	Channel();
	~Channel();
};

