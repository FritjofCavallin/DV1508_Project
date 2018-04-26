#include "SolutionExplorer.h"

SolutionExplorer::SolutionExplorer(){
	winPosX = 0, winPosY = 626;
	winSizeX = 300, winSizeY = 454;
}

SolutionExplorer::~SolutionExplorer(){}

void SolutionExplorer::draw(){
	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(winPosX, winPosY));
	ImGui::SetWindowSize(ImVec2(winSizeX, winSizeY));

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
	ImGui::Button("Effect_name");
	ImGui::PopStyleColor(3);
	ImGui::PopID();
	
	//---------------------------------------------

	ImGui::SetNextTreeNodeOpen(true);
	ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(1.f, 1.f, 1.f, 1.0f));
	if(ImGui::TreeNode("Emitters")){
		ImGui::PopStyleColor();

		for(int i = 0; i < 3; i++){	//replace with size of emitterTimelineVec
			ImGui::PushID(i);	//why do we need ID? can be removed...
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.f, 0.f, 0.f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.f, 1.f, 0.2f));
			std::string name = "Emitter" + std::to_string(i);
			ImGui::Button(CChar(name));
			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	else{
		ImGui::PopStyleColor();
	}

	//---------------------------------------------

	ImGui::SetNextTreeNodeOpen(true);
	ImGui::PushStyleColor(ImGuiCol_Text, (ImVec4)ImColor::HSV(1.f, 1.f, 1.f, 1.0f));
	if(ImGui::TreeNode("Particles")){
		ImGui::PopStyleColor();

		//...
		ImGui::TreePop();
	}
	else{
		ImGui::PopStyleColor();
	}

	ImGui::End();
}