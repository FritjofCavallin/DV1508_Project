#pragma once

#include "UIContainer.h"

class SolutionExplorer : public UIContainer
{
public:
	SolutionExplorer();
	virtual ~SolutionExplorer();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

