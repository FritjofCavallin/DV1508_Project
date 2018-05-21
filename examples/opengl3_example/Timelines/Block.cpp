#include "Block.h"



Block::Block(TimeInterval t, type::Timeline type)
	: _time(t), _type(type)
{
}


Block::~Block()
{
}

bool Block::overlaps(Block* other)
{
	return !(other->_time._startTime <= _time._startTime && other->_time._endTime <= _time._startTime ||
		other->_time._endTime >= _time._endTime && other->_time._startTime >= _time._endTime);
}

void Block::DrawPropertiesHeader(ImVec2 pos, ImVec2 size){
	ImGui::SameLine(size.x - 220);
	ImGui::Text("Start:");

	ImGui::SameLine(size.x - 177);
	ImGui::PushItemWidth(45);
	ImGui::InputFloat(" ", &_time._startTime, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::SameLine(size.x - 100);
	ImGui::Text("End:");

	ImGui::SameLine(size.x - 72);
	ImGui::PushItemWidth(45);
	if(ImGui::InputFloat("  ", &_time._endTime, 0, 0, 3, ImGuiInputTextFlags_EnterReturnsTrue)){
		//possibly push timeline
	}
	ImGui::PopItemWidth();
	ImGui::Separator();
}

bool Block::contains(Block* other)
{
	return _time._startTime <= other->_time._startTime && _time._endTime >= other->_time._endTime;
}
