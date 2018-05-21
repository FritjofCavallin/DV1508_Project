#include "ForceBlock.h"
#include "../../Other/Constants.h"


ForceBlock::ForceBlock(TimeInterval t)
	: Block(t, type::Particle), _gravityPoint(0,1,0), _force(10.f)
{
	visualName = "Force";
	desc = "A force applied over time";
}

ForceBlock::ForceBlock(TimeInterval t, glm::vec3 forceDir, float force)
	: Block(t, type::Particle), _gravityPoint(forceDir), _force(force)
{
	visualName = "Force";
	desc = "A force applied over time";
}

ForceBlock::~ForceBlock()
{
}

void ForceBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _gravityPoint * _force *  EMIT_STEP / _time.duration();
}

void ForceBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	ImGui::Text(" ");
	ImGui::Text("Force Centerpoint: ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x", &_gravityPoint.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y", &_gravityPoint.y, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("z", &_gravityPoint.z, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::Text("            Force: ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("", &_force, 0, 0, 3);
	ImGui::PopItemWidth();
}