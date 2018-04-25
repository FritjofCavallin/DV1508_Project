#pragma once

#include "imgui.h"

class UIContainer
{
public:
	UIContainer();
	virtual ~UIContainer();
	virtual void draw() = 0;
};

