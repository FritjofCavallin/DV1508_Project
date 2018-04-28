#include "Properties.h"



Properties::Properties()
{
}


Properties::~Properties()
{
}

void Properties::draw(ImVec2 pos, ImVec2 size)
{
	// Common stuff
	ImGui::Begin("Properties", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);



	ImGui::End();
}
