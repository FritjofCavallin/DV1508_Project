#include "SolutionExplorer.h"



SolutionExplorer::SolutionExplorer()
{
}


SolutionExplorer::~SolutionExplorer()
{
}

void SolutionExplorer::draw()
{
	// Common stuff
	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(0, 626));
	ImGui::SetWindowSize(ImVec2(300, 454));




	ImGui::End();
}
