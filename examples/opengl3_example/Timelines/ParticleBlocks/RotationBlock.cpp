#include "RotationBlock.h"
#include "../../Other/Constants.h"


RotationBlock::RotationBlock(TimeInterval t)
	: Block(t, type::Particle), _angVelocityBegin(3.14f/20.f), _angVelocityEnd(3.14f / 3.f)
{
	visualName = "Rotation";
	desc = "Rotate the particle quad";
	iconName = "rotation.png";
}


RotationBlock::~RotationBlock()
{
}

void RotationBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	gpuPart._rotation += glm::mix(_angVelocityBegin, _angVelocityEnd, _time.toRelativeNor(emittTime)) * EMIT_STEP;
}

void RotationBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

	static ImGuiComboFlags link = 0;
	
	ImGui::Text("\n  Rotation speed:");
	ImGui::Text("   Initial:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("   ", &_angVelocityBegin, 0, 0, 3);
	ImGui::PopItemWidth();


	ImGui::Text("    Final: ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("    ", &_angVelocityEnd, 0, 0, 3);
	ImGui::PopItemWidth();

	ImVec2 asd = {145, 76};
	ImGui::SetCursorPos(asd);
	ImGui::CheckboxFlags("link", (unsigned int*)&link, ImGuiComboFlags_NoArrowButton);

	if(link) _angVelocityEnd = _angVelocityBegin;
}