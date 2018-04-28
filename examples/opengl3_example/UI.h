#pragma once

#include <vector>

#include "UIContainer.h"

class UI
{
private:
	std::vector<UIContainer*>	_containers;

public:
	UI();
	~UI();
	void draw(ImVec2 windowSize);
};

