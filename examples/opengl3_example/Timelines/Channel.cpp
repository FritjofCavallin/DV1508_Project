#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

#include "imgui.h"
#include "Channel.h"
#include "Timeline.h"

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

void Channel::correctBlockDuration(Block* draggedBlock, Timeline* timeline, bool left)
{
	if (std::find(_data.begin(), _data.end(), draggedBlock) == _data.end())
	{
		std::cerr << "Attempted to call correctBlockDuration() with a block not contained in the channel called";
	}

	ImGuiIO& io = ImGui::GetIO();

	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		if (_data[i] == draggedBlock)
			continue;

		if (left)
		{
			if (draggedBlock->_time._startTime < _data[i]->_time._endTime && draggedBlock->_time._endTime >= _data[i]->_time._endTime)
			{
				if (io.KeyCtrl)
					_data[i]->_time._endTime = std::fmaxf(draggedBlock->_time._startTime, _data[i]->_time._startTime + minBlockDuration);
				draggedBlock->_time._startTime = _data[i]->_time._endTime;
			}
		}
		else
		{
			if (draggedBlock->_time._endTime > _data[i]->_time._startTime && draggedBlock->_time._startTime <= _data[i]->_time._startTime)
			{
				if (io.KeyCtrl)
					_data[i]->_time._startTime = std::fminf(draggedBlock->_time._endTime, _data[i]->_time._endTime - minBlockDuration);
				draggedBlock->_time._endTime = _data[i]->_time._startTime;
			}
		}
	}

	// Left
	if (draggedBlock->_time._startTime < 0.f)
		draggedBlock->_time._startTime = 0.f;

	// Right
	if (draggedBlock->_time._endTime > timeline->_timeTotal._endTime)
	{
		if (io.KeyCtrl)
		{
			timeline->_timeTotal._endTime = draggedBlock->_time._endTime;
			timeline->_timeShown._endTime = draggedBlock->_time._endTime;
		}
		draggedBlock->_time._endTime = timeline->_timeTotal._endTime;
	}

	if (left)
	{
		if (draggedBlock->_time._startTime > draggedBlock->_time._endTime - minBlockDuration)
			draggedBlock->_time._startTime = draggedBlock->_time._endTime - minBlockDuration;
	}
	else
	{
		if (draggedBlock->_time._endTime < draggedBlock->_time._startTime + minBlockDuration)
			draggedBlock->_time._endTime = draggedBlock->_time._startTime + minBlockDuration;
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
