#pragma once

#include "UIContainer.h"

#include <string>

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer();
	virtual ~SolutionExplorer();

	virtual void draw();

protected:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;

	//std::vector<Timeline*> timelineVec;
};

