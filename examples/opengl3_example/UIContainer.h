#pragma once

#include "imgui.h"

class UIContainer
{
public:
	UIContainer();
	virtual ~UIContainer();
	virtual void draw(ImVec2 pos, ImVec2 size) = 0;
};

