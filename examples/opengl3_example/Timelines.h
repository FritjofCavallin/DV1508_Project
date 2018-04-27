#pragma once

#include "UIContainer.h"

class Timelines : public UIContainer
{
public:
	Timelines();
	virtual ~Timelines();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

