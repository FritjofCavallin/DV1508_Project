#include "BoxVolumeBlock.h"
#include "../../Other/RandFunction.h"


BoxVolumeBlock::BoxVolumeBlock(TimeInterval t)
	: Block(t, type::Emitter), _volumeSize(1.f)
{
	visualName = " Box\nVolume";
	desc = "What volume / shape to spawn from";
}


BoxVolumeBlock::~BoxVolumeBlock()
{
}

void BoxVolumeBlock::applyEmitter(Particle &part, GPUParticle &gpuPart)
{
	gpuPart._position.x += randomFloat(-1, 1) * _volumeSize.x;
	gpuPart._position.y += randomFloat(-1, 1) * _volumeSize.y;
	gpuPart._position.z += randomFloat(-1, 1) * _volumeSize.z;
}

void BoxVolumeBlock::DrawProperties(ImVec2 pos, ImVec2 size){

	ImGui::Text(" ");
	ImGui::Text("Volume size:");
	ImGui::SameLine();
	ImGui::PushItemWidth(45);
	ImGui::InputFloat("x", &_volumeSize.x, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("y", &_volumeSize.y, 0, 0, 3);
	ImGui::SameLine();
	ImGui::InputFloat("z", &_volumeSize.z, 0, 0, 3);
	ImGui::PopItemWidth();
}