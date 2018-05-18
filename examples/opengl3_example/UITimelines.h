#pragma once

#include "UIContainer.h"

class UITimelines : public UIContainer
{
private:

	int						_addingNewBlock;
	int						_holdingBlockId;
	ImVec2					_moveDist;
	bool					_onMenuBar = false;

public:
	UITimelines(Data* data);
	virtual ~UITimelines();
	virtual void draw(ImVec2 pos, ImVec2 size);

private:
	float minBlockWidth = 50.0f;
	ImVec4 handleLeftColor = ImVec4(0.2f, 0.2f, 0.6f, 0.6f);
	ImVec4 handleLeftActiveColor = ImVec4(0.3f, 0.3f, 0.9f, 1.0f);
	ImVec4 handleLeftHoveredColor = ImVec4(0.5f, 0.5f, 0.9f, 1.0f);

	ImVec4 handleRightColor = ImVec4(0.6f, 0.2f, 0.2f, 0.6f);
	ImVec4 handleRightActiveColor = ImVec4(0.9f, 0.3f, 0.3f, 1.0f);
	ImVec4 handleRightHoveredColor = ImVec4(0.9f, 0.5f, 0.5f, 1.0f);
	float menubarHeight = 21.0f;
	float blockHandleWidth = 7.0f;
	// Ratio of a channel taken up by the blocks
	float blockHeightRatio = 0.8f;

	ImVec2 dragDistance;

	void drawHandle(bool left, Block* block, Timeline* timeline, int channelIndex, float channelHeight);
	void drawDraggedBlock(Timeline* timeline, float channelHeight);

	// Modifies the given color based on the modifier
	ImVec4 MC(ImVec4 in, float mod)
	{
		return ImVec4(std::min(in.x + mod, 1.f), std::min(in.y + mod, 1.f), std::min(in.z + mod, 1.f), 0.7);
	}
};

