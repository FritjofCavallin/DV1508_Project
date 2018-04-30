#include "UIDivider.h"

UIDivider::UIDivider(DivisionDirection dir, float ratio, Data* data, UIContainer* first, UIContainer* second)
{
	this->data = data;
	this->dir = dir;
	this->ratio = ratio;
	this->first = first;
	this->second = second;

	if (ratio < 0.0f)
		ratio = 0.0f;
	if (ratio > 1.0f)
		ratio = 1.0f;
}

UIDivider::~UIDivider()
{
	delete first;
	delete second;
}

void UIDivider::draw(ImVec2 pos, ImVec2 size)
{
	// The +1's and -1's are used to stack the window borders on top of each other, preventing double borders
	if (dir == DivisionDirection::HORIZONTAL)
	{
		first->draw(pos, ImVec2(size.x, size.y * ratio));
		second->draw(ImVec2(pos.x, pos.y + size.y * ratio - 1), ImVec2(size.x, size.y * (1.0f - ratio) + 1));
	}
	else
	{
		first->draw(pos, ImVec2(size.x * ratio, size.y));
		second->draw(ImVec2(pos.x + size.x * ratio - 1, pos.y), ImVec2(size.x * (1.0f - ratio) + 1, size.y));
	}
}
