#pragma once

#include "UIContainer.h"
#include "camera.h"

class Previewer : public UIContainer
{
public:

	Previewer(Data* data);
	virtual ~Previewer();
	virtual void draw(ImVec2 pos, ImVec2 size);
};

