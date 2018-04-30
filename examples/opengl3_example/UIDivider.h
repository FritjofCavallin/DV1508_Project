#pragma once

#include "UIContainer.h"

// Divides a rectangular area in two according to a ratio. Calculates size for children and passes drawing command to them.

class UIDivider : public UIContainer
{
public:
	enum DivisionDirection { HORIZONTAL, VERTICAL };

	UIDivider(DivisionDirection dir, float ratio, Data* data, UIContainer* first, UIContainer* second);
	virtual ~UIDivider();
	virtual void draw(ImVec2 pos, ImVec2 size);
private:
	UIContainer* first;
	UIContainer* second;
	DivisionDirection dir;
	float ratio;	// [0..1]
};
