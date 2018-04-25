#include "Previewer.h"



Previewer::Previewer()
{
}


Previewer::~Previewer()
{
}


void Previewer::draw()
{
	// Common stuff
	ImGui::Begin("Previewer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(ImVec2(0, 26));
	ImGui::SetWindowSize(ImVec2(900, 600));




	ImGui::End();
}
