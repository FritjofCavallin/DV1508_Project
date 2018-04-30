#pragma once

#include <vector>

#include "UIContainer.h"
#include "Timelines/Data.h"

class UI
{
private:
	std::vector<UIContainer*>	_containers;
	Data* data;

public:
	UI(Data* data);
	~UI();
	void draw(ImVec2 windowSize);
};

