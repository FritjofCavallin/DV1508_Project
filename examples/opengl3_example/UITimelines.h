#pragma once

#include "UIContainer.h"

class UITimelines : public UIContainer
{
private:
	struct BlockInfo
	{
		std::string _name;
		std::string _desc;
	};

	int						_addingNewBlock;
	int						_holdingBlockId;
	ImVec2					_moveDist;
	std::vector<BlockInfo>*	_blockInfos[3];
	Block*					_movingBlock;

public:
	UITimelines(Data* data);
	virtual ~UITimelines();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

