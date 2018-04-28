#include "SolutionExplorer.h"

SolutionExplorer::SolutionExplorer(){
	firstDraw = true;
	drawNewFilePopup = false;
}

SolutionExplorer::~SolutionExplorer(){}

void SolutionExplorer::draw(ImVec2 pos, ImVec2 size){
	// Common stuff
	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	if(firstDraw){
		winPos = pos;
		winSize = size;
	}

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
	if(ImGui::Button(" Add File "))
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
	if(ImGui::Button(" Save "))
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
	if(ImGui::Selectable(CChar(AddSpace("Effect_name")), false, ImGuiSelectableFlags_AllowDoubleClick))
		if(ImGui::IsMouseDoubleClicked(0))
			OpenFileInWorkspace(/*effect*/);

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

			if(ImGui::Selectable(CChar(AddSpace("Emitter" + std::to_string(i))), false, ImGuiSelectableFlags_AllowDoubleClick))
				if(ImGui::IsMouseDoubleClicked(0))
					OpenFileInWorkspace(/*emitterTimelineVec.at(i)*/);

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

	if(drawNewFilePopup) ImGui::OpenPopup("Create New File");
	if(ImGui::BeginPopupModal("Create New File")){
		drawNewFilePopup = false;

		static int fileTypeChoice = 0;
		ImGui::RadioButton("Particle", &fileTypeChoice, 0); ImGui::SameLine();
		ImGui::RadioButton("Emitter", &fileTypeChoice, 1);

		static char str0[256] = "";
		ImGui::InputText("File name", str0, IM_ARRAYSIZE(str0));

		static ImGuiComboFlags openChoiceFlags = 0;
		if(ImGui::CheckboxFlags("Open file in workspace", (unsigned int*)&openChoiceFlags, ImGuiComboFlags_NoArrowButton)){ }

		if(ImGui::Button("OK", ImVec2(120, 0))){
			AddNewFile(str0, fileTypeChoice, (openChoiceFlags == 32 ? true : false));
			ImGui::CloseCurrentPopup();
		}
		ImGui::SetItemDefaultFocus();
		ImGui::SameLine();
		if(ImGui::Button("Cancel", ImVec2(120, 0))) ImGui::CloseCurrentPopup();
		ImGui::EndPopup();
	}

	//---------------------------------------------

	ImGui::End();
}

std::string SolutionExplorer::AddSpace(std::string base, int comp){
	//1 space = 7 pixels wide
	int spaces = (int)((winSize.x - comp - base.length()) / 7);
	for(int i = 0; i < spaces; ++i) base += " ";

	return base;
}

void SolutionExplorer::AddNewFile(std::string name, bool isEmitter, bool open){
	//...
}

void SolutionExplorer::AddExistingFile(){
	//empty
}

void SolutionExplorer::OpenFileInWorkspace(/*Timeline* file*/){
	//...
}

//VS_Text
void SolutionExplorer::Style_VS_Text_s(){
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.4f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.4f));
}
void SolutionExplorer::Style_VS_Text_f(){
	ImGui::PopStyleColor(5);
}

//VS_Node
void SolutionExplorer::Style_VS_Node_s(){
	ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(0.3f, 0.3f, 1.f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderActive, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.0f));
}
void SolutionExplorer::Style_VS_Node_f(){
	ImGui::PopStyleColor(3);
}