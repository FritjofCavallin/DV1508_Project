#include "Properties.h"

Properties::Properties(Data* data){
	this->data = data;

	currBlock = nullptr;

	firstDraw = true;
}


Properties::~Properties(){
}

void Properties::draw(ImVec2 pos, ImVec2 size){
	// Common stuff
	ImGui::Begin("Properties", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	if(firstDraw){
		winPos = pos;
		winSize = size;
	}

	if(data->_selectedBlock){
		//show block properties
		data->_selectedBlock->DrawProperties(pos, size);
	}
	else{
		//show help prompt
		ImGui::Text("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");	//beautiful solution
		ImGui::Text(CenterString("Select timeline block to display its properties").c_str());
	}

	if(firstDraw) firstDraw = false;
	ImGui::End();
}

std::string Properties::AddSpace(std::string base, int comp){
	//1 space = 7 pixels wide
	int spaces = (int)((winSize.x - comp - (base.length()*7)) / 7);
	for(int i = 0; i < spaces; ++i) base += " ";

	return base;
}

std::string Properties::CenterString(std::string base, int comp){
	std::string newStr = "";
	int spaces = (int)(((winSize.x - comp - (base.length()*7)) / 2) / 7);	//OBS! fkd

	for(int i = 0; i < spaces; ++i) newStr += " ";
	newStr += base;

	return newStr;
}

//VS_Text
void Properties::Style_VS_Text_s(){
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.4f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.4f));
}
void Properties::Style_VS_Text_f(){
	ImGui::PopStyleColor(5);
}

//VS_Node
void Properties::Style_VS_Node_s(){
	ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0.3f, 0.3f, 1.f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));
}
void Properties::Style_VS_Node_f(){
	ImGui::PopStyleColor(3);
}