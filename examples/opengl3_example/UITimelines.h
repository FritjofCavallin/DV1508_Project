#pragma once

#include "UIContainer.h"

class UITimelines : public UIContainer
{
public:
	UITimelines(Data* data);
	virtual ~UITimelines();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

