#include "Previewer.h"



Previewer::Previewer()
{
}


Previewer::~Previewer()
{
}


void Previewer::draw(ImVec2 pos, ImVec2 size)
{
	// Common stuff
	ImGui::Begin("Previewer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);




	ImGui::End();
}
