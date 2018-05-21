#include "ScaleBlock.h"



ScaleBlock::ScaleBlock(TimeInterval t)
	: Block(t, type::Particle)
{
	visualName = "Scale";
	desc = "Change size of the particle";
	iconName = "Scale.png";
}


ScaleBlock::~ScaleBlock()
{
}

void ScaleBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._size *= glm::mix(_scaleBegin, _scaleEnd, _time.toRelativeNor(emittTime));
}

void ScaleBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

	static ImGuiComboFlags link = 0;

	ImGui::Text("\n  Scale:");
	ImGui::Text("   Initial:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x##1", &_scaleBegin.x, 0, 0, 3);
	ImGui::SameLine(/*148*/);
	ImGui::InputFloat("y##1", &_scaleBegin.y, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::Text("   Final:  ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x##2", &_scaleEnd.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y##2", &_scaleEnd.y, 0, 0, 3);
	ImGui::PopItemWidth();

	ImVec2 asd = {220, 76};
	ImGui::SetCursorPos(asd);
	ImGui::CheckboxFlags("link", (unsigned int*)&link, ImGuiComboFlags_NoArrowButton);

	if(link) _scaleEnd = _scaleBegin;
}