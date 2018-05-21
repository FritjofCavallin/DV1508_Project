#include "ConstantForce.h"
#include "../../Other/Constants.h"


ConstantForce::ConstantForce(TimeInterval t)
	: Block(t, type::Particle), _forceDir(0,-1,0), _gravity(9.82f)
{
	visualName = "Constant\n Force";
	desc = "Apply a constant force";
}


ConstantForce::~ConstantForce()
{
}

void ConstantForce::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	part._velocity += _forceDir * _gravity *  EMIT_STEP;
}

void ConstantForce::DrawProperties(ImVec2 pos, ImVec2 size){
	ImGui::Text(" ");
	ImGui::Text("Force direction: ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x", &_forceDir.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y", &_forceDir.y, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("z", &_forceDir.z, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::Text("          Force: ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("", &_gravity, 0, 0, 3);
	ImGui::PopItemWidth();
}