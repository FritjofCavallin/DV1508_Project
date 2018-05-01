#pragma once
#include "Block.h"
#include <vector>

/* Timeline channel
*/
class Channel
{
public:
	std::vector<Block*> _data; // vector = simple solution, could be improved if needed

	bool isEmpty();

	// Returns true if block does not overlap any other blocks in the channel
	bool blockFits(Block* block);

	Channel();
	~Channel();


};

