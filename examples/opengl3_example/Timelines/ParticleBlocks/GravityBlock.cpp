#include "GravityBlock.h"
#include "../../Other/Constants.h"


GravityBlock::GravityBlock(TimeInterval t)
	: Block(t, type::Particle), _gravityPoint(0,0,0), _gravity(9.82f)
{
	visualName = "Gravity";
	desc = "Accelerate toward a point";
	iconName = "Gravity.png";
}
GravityBlock::GravityBlock(TimeInterval t, glm::vec3 gravityPoint, float constantForce)
	: Block(t, type::Particle), _gravityPoint(gravityPoint), _gravity(constantForce)
{
	visualName = "Gravity";
	desc = "Accelerate toward a point";
	iconName = "Gravity.png";
}


GravityBlock::~GravityBlock()
{
}

void GravityBlock::applyParticle(float emitterTime, Particle &part, GPUParticle &gpuPart)
{
	// Accelerate toward the gravity point
	part._velocity += glm::normalize(_gravityPoint - gpuPart._position) * _gravity *  EMIT_STEP;
}

void GravityBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	ImGui::Text(" ");
	ImGui::Text("  Point of gravity:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x", &_gravityPoint.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y", &_gravityPoint.y, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("z", &_gravityPoint.z, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::Text("Gravitational pull:");
	ImGui::PushItemWidth(45);
	ImGui::SameLine();
	ImGui::InputFloat(" ##1", &_gravity, 0, 0, 3);
}