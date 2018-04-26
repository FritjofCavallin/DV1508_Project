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

	//ImGui::Columns(1, "solutionTree");
	//if(ImGui::TreeNode("Effect_name")){
	//	if(ImGui::TreeNode("Emitters")){
	//		ImGui::BulletText("Emitter1");
	//		ImGui::BulletText("Emitter2");
	//		ImGui::BulletText("Emitter3");
	//		ImGui::TreePop();
	//	}
	//	if(ImGui::TreeNode("Particles")){
	//		ImGui::BulletText("Particle1");
	//		ImGui::BulletText("Particle2");
	//		ImGui::BulletText("Particle3");
	//		ImGui::TreePop();
	//	}
	//	ImGui::TreePop();
	//}
	//ImGui::NextColumn();
	//ImGui::Columns(1);

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));
	ImGui::Button("Effect_name");
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	//ImGui::Columns(1, "solutionTree");
	//if(ImGui::TreeNode("Effect_name")){
	if(ImGui::TreeNode("Emitters")){
		for(int i = 0; i < 3; i++){	//replace with size of timelineVec
			ImGui::PushID(i);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
			std::string name = "Emitter" + std::to_string(i);
			ImGui::Button(CChar(name));
			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
		ImGui::TreePop();
	}
	if(ImGui::TreeNode("Particles")){

		ImGui::TreePop();
	}
	//	ImGui::TreePop();
	//}

	ImGui::End();
}

const char* SolutionExplorer::CChar(std::string& s){
	return s.data();
}

char* SolutionExplorer::Char(std::string& s){
	return &s[0];
}