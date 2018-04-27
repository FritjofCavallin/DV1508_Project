#include "SolutionExplorer.h"



SolutionExplorer::SolutionExplorer()
{
}


SolutionExplorer::~SolutionExplorer()
{
}

void SolutionExplorer::draw(ImVec2 pos, ImVec2 size)
{
	// Common stuff
	ImGui::Begin("SolutionExplorer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);




	ImGui::End();
}
