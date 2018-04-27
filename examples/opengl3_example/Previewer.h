#pragma once

#include "UIContainer.h"

class Previewer : public UIContainer
{
public:
	Previewer();
	virtual ~Previewer();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

