#include "ColorBlock.h"
#include "imgui_internal.h"
#include "../Data.h"
#include "../../Other/GLFuncs.h"


static GLuint lin = 0, linInv, expVal, expInv;

ColorBlock::ColorBlock(TimeInterval t, Data &data)
	: Block(t, type::Particle), _colorBegin(1.f), _colorEnd(1.f), interpolation(linear)
{
	visualName = "Color";
	desc = "Change color of the texture and particle";
	iconName = "Color.png";

	if (!lin)
	{
		loadTexture("Linear.png", lin);
		loadTexture("LinearDecr.png", linInv);
		loadTexture("Exp.png", expVal);
		loadTexture("ExpInv.png", expInv);
	}
}


ColorBlock::~ColorBlock()
{
}

void ColorBlock::applyParticle(float emittTime, Particle &part, GPUParticle &gpuPart)
{
	const float c = 100.f;
	float tRel = _time.toRelativeNor(emittTime);
	switch (interpolation)
	{
	case linearDecrease:
		tRel = 1.f - tRel;
		break;
	case exponential:
		tRel = 1/c * std::pow(c, tRel);
		break;
	case exponentialInv:
		tRel = std::log(c * tRel) / std::log(c);
		break;
	case linear:
	default:
		break;
	}
	gpuPart._color *= glm::mix(_colorBegin, _colorEnd, tRel);
}

void ColorBlock::DrawProperties(ImVec2 pos, ImVec2 size){
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

	ImGui::Text("Interpolation:");
	const ImVec2 s(40, 40);
	const ImVec4 tC(0.55, 0.55, 0.55, 1), tNor(1,1,1,1);
	ImGui::BeginChild("");
	ImGui::Columns(2, "", false);
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(lin), s, ImVec2(0, 0), ImVec2(1, 1), 1, ImVec4(0, 0, 0, 0), interpolation == linear ? tC : tNor))
		interpolation =  linear;
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(expVal), s, ImVec2(0, 0), ImVec2(1, 1), 1, ImVec4(0, 0, 0, 0), interpolation == exponential ? tC : tNor))
		interpolation = exponential;

	ImGui::NextColumn();	//CCOLUMN
	
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(linInv), s, ImVec2(0, 0), ImVec2(1, 1), 1, ImVec4(0, 0, 0, 0), interpolation == linearDecrease ? tC : tNor))
		interpolation = linearDecrease;
	if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(expInv), s,ImVec2(0,0), ImVec2(1, 1),1,ImVec4(0,0,0,0), interpolation == exponentialInv ? tC : tNor))
		interpolation = exponentialInv;
	ImGui::EndChild();
		
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