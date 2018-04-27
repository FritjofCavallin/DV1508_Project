#include "SolutionExplorer.h"

SolutionExplorer::SolutionExplorer(){
	winPosX = 0, winPosY = 626;
	winSizeX = 300, winSizeY = 454;

	firstDraw = true;
	drawNewFilePopup = false;
}

SolutionExplorer::~SolutionExplorer(){}

void SolutionExplorer::draw(){

	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(winPosX, winPosY));
	ImGui::SetWindowSize(ImVec2(winSizeX, winSizeY));

	//---------------------------------------------
	//header buttons

	ImGui::PushID(0);
	Style_VS_Text_s();
	if(ImGui::Button(" Properties "))
		ImGui::OpenPopup("miniMenu1");
	if(ImGui::BeginPopup("miniMenu1")){
		ImGui::Selectable("alpha");
		ImGui::Selectable("beta");
		ImGui::Selectable("gamma");
		ImGui::EndPopup();
	}
	ImGui::PopID();

	ImGui::SameLine();

	ImGui::PushID(0);
	if(ImGui::Button("  Add File  "))
		ImGui::OpenPopup("miniMenu2");
	if(ImGui::BeginPopup("miniMenu2")){
		if(ImGui::Selectable("New file")){
			drawNewFilePopup = true;
		}
		if(ImGui::Selectable("Existing file"))
			AddExistingFile();
		ImGui::EndPopup();
	}
	ImGui::PopID();

	ImGui::SameLine();

	ImGui::PushID(0);
	if(ImGui::Button("  Save  "))
		ImGui::OpenPopup("miniMenu3");
	if(ImGui::BeginPopup("miniMenu3")){
		ImGui::Selectable("alpha");
		ImGui::Selectable("beta");
		ImGui::Selectable("gamma");
		ImGui::EndPopup();
	}
	ImGui::PopID();
	Style_VS_Text_f();

	//---------------------------------------------
	//effect button

	ImGui::Columns(1, "explorer", false);
	ImGui::Separator();

	ImGui::PushID(0);
	Style_VS_Text_s();
	ImGui::Button(CChar(AddSpace("Effect_name")));
	Style_VS_Text_f();
	ImGui::PopID();
	
	//---------------------------------------------
	//drop-down 1 (emitters)

	if(firstDraw) ImGui::SetNextTreeNodeOpen(true);
	Style_VS_Node_s();
	if(ImGui::TreeNode(CChar(AddSpace("Emitters")))){
		Style_VS_Node_f();

		for(int i = 0; i < 3; i++){	//replace with size of emitterTimelineVec
			ImGui::PushID(i);
			Style_VS_Text_s();
			ImGui::Button(CChar(AddSpace("Emitter" + std::to_string(i))));
			Style_VS_Text_f();
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	else{
		Style_VS_Node_f();
	}

	//---------------------------------------------
	//drop-down 2 (particles)

	if(firstDraw){
		ImGui::SetNextTreeNodeOpen(true);
		firstDraw = false;
	}
	Style_VS_Node_s();
	if(ImGui::TreeNode(CChar(AddSpace("Particles")))){
		Style_VS_Node_f();

		//...
		ImGui::TreePop();
	}
	else{
		Style_VS_Node_f();
	}

	//---------------------------------------------
	//New file pop-up window

	if(drawNewFilePopup) ImGui::OpenPopup("NewFileWindow");
	if(ImGui::BeginPopupModal("NewFileWindow")){
		drawNewFilePopup = false;

		ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
		ImGui::Separator();

		if(ImGui::Button("OK", ImVec2(120, 0))){ ImGui::CloseCurrentPopup(); }
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if(ImGui::Button("Cancel", ImVec2(120, 0))){ ImGui::CloseCurrentPopup(); }
		ImGui::EndPopup();
	}

	//---------------------------------------------

	ImGui::End();
}

std::string SolutionExplorer::AddSpace(std::string base, int comp){
	//1 space = 7 pixels wide
	int spaces = (int)((winSizeX - comp - base.length()) / 7);
	for(int i = 0; i < spaces; ++i) base += " ";

	return base;
}

void SolutionExplorer::AddNewFile(){

}

void SolutionExplorer::AddExistingFile(){
	//empty
}

void SolutionExplorer::Style_VS_Text_s(){
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.4f));
}
void SolutionExplorer::Style_VS_Text_f(){
	ImGui::PopStyleColor(3);
}

void SolutionExplorer::Style_VS_Node_s(){
	ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0.3f, 0.3f, 1.f, 1.0f));

	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));

}
void SolutionExplorer::Style_VS_Node_f(){
	ImGui::PopStyleColor(3);
}