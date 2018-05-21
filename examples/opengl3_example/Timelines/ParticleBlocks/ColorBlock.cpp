#include "ColorBlock.h"
#include "imgui_internal.h"


ColorBlock::ColorBlock(TimeInterval t)
	: Block(t, type::Particle), _colorBegin(1.f), _colorEnd(1.f)
{
	visualName = "Color";
	desc = "Change color of the texture and particle";
	iconName = "testicon2.png";
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

	ImGui::Text(" ");

	static ImVec4 color;
	static int link = 0;

	ImGuiColorEditFlags flags = ImGuiColorEditFlags_Float | ImGuiColorEditFlags_RGB | 
		ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar;

	color.x = _colorBegin.x;
	color.y = _colorBegin.y;
	color.z = _colorBegin.z;
	color.w = _colorBegin.w;

	ImGui::Columns(3, "", false);
	ImGui::PushItemWidth(-1);	//fking BS solution!
	ImGui::ColorPicker4("   ", (float*)&color, flags, NULL);

	_colorBegin.x = color.x;
	_colorBegin.y = color.y;
	_colorBegin.z = color.z;
	_colorBegin.w = color.w;

	ImGui::NextColumn();	//COLUMN

	ImGui::Text("\n\n");
	ImGui::Text("         ");
	ImGui::SameLine();
	ImGui::CheckboxFlags("link", (unsigned int*)&link, ImGuiComboFlags_NoArrowButton);

	ImGui::Text("\n\n\n");

	ImGui::Text("Interpolation type:");
	static int interpolation = 0;
	ImGui::RadioButton("##1", &interpolation, 0);
	ImGui::RadioButton("##2", &interpolation, 1);
	ImGui::RadioButton("##3", &interpolation, 2);
	ImGui::RadioButton("##4", &interpolation, 3);

	ImGui::NextColumn();	//COLUMN

	if(link){
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.3f);
	}

	color.x = _colorEnd.x;
	color.y = _colorEnd.y;
	color.z = _colorEnd.z;
	color.w = _colorEnd.w;

	ImGui::PushItemWidth(-1);
	ImGui::ColorPicker4("    ", (float*)&color, flags, NULL);

	if(link){
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
		_colorEnd = _colorBegin;
	}
	else{
		_colorEnd.x = color.x;
		_colorEnd.y = color.y;
		_colorEnd.z = color.z;
		_colorEnd.w = color.w;
	}
}