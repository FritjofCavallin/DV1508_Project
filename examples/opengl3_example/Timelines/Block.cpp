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

bool Block::DrawPropertiesHeader(ImVec2 pos, ImVec2 size){
	bool changed = false;

	//block name
	{
		std::string type = "";
		if(_type == type::Timeline::Particle) type = "Particle : ";
		if(_type == type::Timeline::Emitter) type = "Emitter : ";
		if(_type == type::Timeline::Effect) type = "Effect : ";

		std::string name = visualName;
		size_t found = 0;

		for(size_t i = 0; i < name.length(); ++i)
			if(name[i] == '\n') found = i;

		if(found > 0) name.replace(found, 1, "");
		
		std::string print = type + name;
		ImGui::Text(print.c_str());
	}

	//block size adjustment
	{

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
			changed = true;
		}
		ImGui::PopItemWidth();
		ImGui::Separator();
	}

	return changed;
}

void Block::DrawPropertiesFooter(ImVec2 pos, ImVec2 size){
	int lines = desc.length() / (size.x / 7);
	lines++;

	ImVec2 asd = {20, size.y-(lines*22)};	//halp me god
	ImGui::SetCursorPos(asd);

	ImGui::Text(desc.c_str());
}

bool Block::contains(Block* other)
{
	return _time._startTime <= other->_time._startTime && _time._endTime >= other->_time._endTime;
}
