#include "SpawnBlock.h"


InitialEmissionParams::InitialEmissionParams() :
	_initAmount(1), _endAmount(20),
	_minSize(0.4f, 0.4f),	_maxSize(0.5f, 0.5f),
	_emitOrigin(0.f), _emitDir(0,1.f,0),
	_minRotation(0), _maxRotation(3.14f*2),
	_minForce(0.5f), _maxForce(2.f)
{
}


SpawnBlock::SpawnBlock(TimeInterval t)
	: Block(t, type::Emitter), _params()
{
	visualName = "Amount";
	desc = "The amount of particles to spawn";
}

SpawnBlock::SpawnBlock(TimeInterval t, InitialEmissionParams &p) 
	: Block(t, type::Emitter), _params(p)
{
	visualName = "Amount";
	desc = "The amount of particles to spawn";
}

SpawnBlock::~SpawnBlock()
{
}

void SpawnBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

	//---
	ImGui::Text("Amount");
	ImGui::Text("   Initial:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("", &_params._initAmount, 0, 0, 3);
	ImGui::SameLine(120);
	ImGui::Text("     Final:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("   ", &_params._endAmount, 0, 0, 3);

	//---
	ImGui::Text("Size");
	ImGui::Text("   Minimum:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x", &_params._minSize.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y", &_params._minSize.y, 0, 0, 3);
	ImGui::PopItemWidth();

	ImGui::Text("   Maxumum:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x ", &_params._maxSize.x, 0, 0, 3);
	ImGui::SameLine(155);
	ImGui::InputFloat("y ", &_params._maxSize.y, 0, 0, 3);
	ImGui::PopItemWidth();

	//---
	ImGui::Text("Origin");
	ImGui::Text("  ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x  ", &_params._emitOrigin.x, 0, 0, 3);
	ImGui::SameLine(90);
	ImGui::InputFloat("y  ", &_params._emitOrigin.y, 0, 0, 3);
	ImGui::SameLine(153);
	ImGui::InputFloat("z  ", &_params._emitOrigin.z, 0, 0, 3);
	ImGui::PopItemWidth();

	//---
	ImGui::Text("Direction");
	ImGui::Text("  ");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x  ", &_params._emitDir.x, 0, 0, 3);
	ImGui::SameLine(90);
	ImGui::InputFloat("y  ", &_params._emitDir.y, 0, 0, 3);
	ImGui::SameLine(153);
	ImGui::InputFloat("z  ", &_params._emitDir.z, 0, 0, 3);
	ImGui::PopItemWidth();

	//---
	ImGui::Text("Rotation");
	ImGui::Text("   Min:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("    ", &_params._minRotation, 0, 0, 3);
	ImGui::SameLine(100);
	ImGui::Text("   Max:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("     ", &_params._maxRotation, 0, 0, 3);

	//---
	ImGui::Text("Force");
	ImGui::Text("   Min:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("    ", &_params._minForce, 0, 0, 3);
	ImGui::SameLine(100);
	ImGui::Text("   Max:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("     ", &_params._maxForce, 0, 0, 3);
}