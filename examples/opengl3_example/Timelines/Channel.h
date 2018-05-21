#pragma once
#include "Block.h"
#include <vector>


class Timeline;
/* Timeline channel
*/
class Channel
{
public:
	std::vector<Block*> _data; // vector = simple solution, could be improved if needed

	bool isEmpty();

	// Returns true if block does not overlap any other blocks in the channel
	bool blockFits(Block* block);

	// Called when dragging the width of draggedBlock
	// The duration of draggedBlock will be corrected if it
	// overlaps that of another block or if it's dragged outside the timeline.
	// <left> should be true if the left handle is dragged and false otherwise
	void correctBlockDuration(Block* draggedBlock, Timeline* timeline, bool left);

	Channel();
	~Channel();

	float minBlockDuration = 0.05f;
};

