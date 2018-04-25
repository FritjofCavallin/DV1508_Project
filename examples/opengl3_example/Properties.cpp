#include "Properties.h"



Properties::Properties()
{
}


Properties::~Properties()
{
}

void Properties::draw()
{
	// Common stuff
	ImGui::Begin("Properties", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(300, 626));
	ImGui::SetWindowSize(ImVec2(600, 454));



	ImGui::End();
}
