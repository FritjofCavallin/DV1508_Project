#pragma once

#include "UIContainer.h"

class UITimelines : public UIContainer
{
private:
	int		_addingNewBlock;
	int		_holdingBlockId;
	ImVec2	_moveDist;
	std::vector<std::string>* blockNames[3];
	Block*	_movingBlock;

public:
	UITimelines(Data* data);
	virtual ~UITimelines();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

