#pragma once

#include "UIContainer.h"

class Properties : public UIContainer
{
public:
	Properties();
	virtual ~Properties();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

