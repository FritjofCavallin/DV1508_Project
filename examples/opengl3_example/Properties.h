#pragma once

#include "UIContainer.h"
#include <string>

class Properties : public UIContainer
{
public:
	Properties();
	virtual ~Properties();
	virtual void draw(ImVec2 pos, ImVec2 size);

	std::string AddSpace(std::string base, int comp);
	std::string CenterString(std::string base, int comp);
private:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;
	ImVec2 winPos, winSize;

	//Block* currBlock;

	bool firstDraw;
};

