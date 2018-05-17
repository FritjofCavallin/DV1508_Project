#include "ColorBlock.h"



ColorBlock::ColorBlock(TimeInterval t)
	: Block(t, type::Particle), _colorBegin(1.f), _colorEnd(1.f)
{
	visualName = "Color";
	desc = "Change color of the texture and particle";
}


ColorBlock::~ColorBlock()
{
}

void ColorBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	float tRel = _time.toRelativeNor(emittTime);
	gpuPart._color *= glm::mix(_colorBegin, _colorEnd, tRel);
}

void ColorBlock::DrawProperties(ImVec2 pos, ImVec2 size){
	DrawPropertiesHeader(pos, size);

	static ImVec4 color;
	static int time = 0;
	if(time){
		color.x = _colorEnd.x;
		color.y = _colorEnd.y;
		color.z = _colorEnd.z;
	}
	else{
		color.x = _colorBegin.x;
		color.y = _colorBegin.y;
		color.z = _colorBegin.z;
	}

	ImGui::Columns(2, "", false);
	ImGuiColorEditFlags flags = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_RGB | 
		ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar;
	ImGui::PushItemWidth(-1);	//fking BS solution!
	ImGui::ColorPicker4(" ", (float*)&color, flags, NULL);

	if(time){
		_colorEnd.x = color.x;
		_colorEnd.y = color.y;
		_colorEnd.z = color.z;
	}
	else{
		_colorBegin.x = color.x;
		_colorBegin.y = color.y;
		_colorBegin.z = color.z;

	}

	ImGui::NextColumn();
	ImGui::Text("\n\n\n");
	ImGui::RadioButton("Start Color", &time, 0);
	ImGui::RadioButton("End Color", &time, 1);


	//ImGui::Separator();	//doesnt work in a column
	ImGui::Text("\n\n\n");

	ImGui::Text("Interpolation type:");
	static int interpolation = 0;
	ImGui::RadioButton("some stuff", &interpolation, 0);
	ImGui::RadioButton("some other stuff", &interpolation, 1);
}