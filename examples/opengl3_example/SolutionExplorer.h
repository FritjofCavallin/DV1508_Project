#pragma once

#include "UIContainer.h"

#include <string>

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer();
	virtual ~SolutionExplorer();

	virtual void draw();
	const char* SolutionExplorer::CChar(std::string& s);
	char* SolutionExplorer::Char(std::string& s);

protected:
	//ImGui
	int winPosX, winPosY, winSizeX, winSizeY;

	//std::vector<Timeline*> timelineVec;
};

