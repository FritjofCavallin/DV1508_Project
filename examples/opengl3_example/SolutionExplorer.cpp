#include "SolutionExplorer.h"

SolutionExplorer::SolutionExplorer(){
	winPosX = 0;
	winPosY = 626;
	winSizeX = 300;
	winSizeY = 454;
}

SolutionExplorer::~SolutionExplorer(){
}

void SolutionExplorer::draw(){
	// Common stuff
	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(winPosX, winPosY));
	ImGui::SetWindowSize(ImVec2(winSizeX, winSizeY));




	ImGui::End();
}
