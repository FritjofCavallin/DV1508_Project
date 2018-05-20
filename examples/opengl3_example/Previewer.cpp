#include "Previewer.h"

#include <string>
#include "Window/PreviewWindow.h"

Previewer::Previewer(Data * data)
{
	this->data = data;
}

Previewer::~Previewer()
{
}


void Previewer::draw(ImVec2 pos, ImVec2 size)
{

	data->getPreview()->resize(size.x, size.y);
	// Draw 2D
	ImGui::Begin("Previewer", 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar);
	ImGui::SetWindowPos(pos);
	ImGui::SetWindowSize(size);

	ImGui::Image(data->getPreview()->getWindowTex(), ImGui::GetContentRegionAvail(), ImVec2(0, 0), ImVec2(1, -1));

	ImGui::End();
}
