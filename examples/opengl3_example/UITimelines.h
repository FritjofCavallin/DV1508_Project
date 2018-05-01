#pragma once

#include "UIContainer.h"

class UITimelines : public UIContainer
{
public:
	UITimelines(Data* data);
	virtual ~UITimelines();
	virtual void draw(ImVec2 pos, ImVec2 size);

private:
	float minBlockWidth = 50.0f;
	ImVec4 handleColor = ImVec4(0.2f, 0.2f, 0.6f, 0.6f);
	ImVec4 handleActiveColor = ImVec4(0.3f, 0.3f, 0.9f, 1.0f);
	ImVec4 handleHoveredColor = ImVec4(0.5f, 0.5f, 0.9f, 1.0f);
	float menubarHeight = 21.0f;
	float blockHandleWidth = 7.0f;

	ImVec2 dragDistance;

	void drawHandle(bool left, Block* block, Timeline* timeline, int channelIndex, float channelHeight);
};

